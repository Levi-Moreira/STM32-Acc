/* Includes */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include <stdio.h>
#include <string.h>
#include "tm_stm32f4_lis302dl_lis3dsh.h"
#include "DTW.h"
#include "LinkedList.h"
#include "serial.h"
#include "infra.h"
#include "time.h"
#include "tm_stm32f4_usart.h"
#include "tm_stm32f4_watchdog.h"

void setup();
/**
 * Formats a number to send a light command, the format Should be CMD+number+%
 * param lightStep the number to be transformed into a command
 */
void sendLightCommand(int lightStep);
void recognizeGesture(LinkedList *signalX, LinkedList *signalY, LinkedList *signalZ, int size);

//holds the connected module ID 1-Door 2-Lights
int deviceID = -1;

//if a pairing happened
int isPaired = 0;

//Should allow door gestures
int activeCommandDoor = 0;

//Should allow light gestures
int activeCommandLight = 0;

//Count the lgiht steps
int lightSteps = -1;

// Commands
const unsigned char BL_CMD_ASK_FOR_IDENTIFICATION[5] = "CMDI%";
const unsigned char BL_CMD_RESET[5] = "CMDR%";
const unsigned char BL_CMD_LAMP_GET_STEP[5] = "CMDS%";
const unsigned char BL_CMD_DOOR_OPEN[6] = "CMD1%\n";
const unsigned char BL_CMD_DOOR_CLOSE[6] = "CMD0%\n";
char BL_CMD_LAMP_STEP[7] = "CMD%d%\n";

// Gestures
#define GESTURE_DOOR_OPEN 0
#define GESTURE_DOOR_CLOSE 1
#define GESTURE_LIGHT_UP 2
#define GESTURE_LIGHT_DOWN 3

#define LIGHT_STEP_DELTA 16
#define LIGHT_STEP_MIN 1
#define LIGHT_STEP_MAX 128

#define BL_DEVICE_DOOR 1
#define BL_DEVICE_LAMP 2

float variance(float *array, int begin, int end);

int main(void) {

	setup();

	USART_puts(USART1, BL_CMD_RESET);

	int count = 0;

	// Signals
	LinkedList *signalX = newLinkedList();
	LinkedList *signalY = newLinkedList();
	LinkedList *signalZ = newLinkedList();

	// Structure for holding the accelerometer data
	TM_LIS302DL_LIS3DSH_t Axes_Data;

	float x, y, z;
	float ax[AVG_SIZE], ay[AVG_SIZE], az[AVG_SIZE];
	float ex[SIZE], ey[SIZE], ez[SIZE];
	float vx[SIZE], vy[SIZE], vz[SIZE];
	int moving = 0;

	float fx, fy, fz;
	float fvx, fvy, fvz;

	fvx = 1;
	fvy = 1;
	fvz = 1;

	int v = 0;

	// Getting values for the initial average
	for(int i = 0; i < AVG_SIZE; i++) {
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		ax[i] = (float) Axes_Data.X;
		ay[i] = (float) Axes_Data.Y;
		az[i] = (float) Axes_Data.Z;
		Delayms(SAMPLEPERIOD);
	}

	// Calculating the average
	fx = average(ax, 0, AVG_SIZE);
	fy = average(ay, 0, AVG_SIZE);
	fz = average(az, 0, AVG_SIZE);

	while(1) {

		//While device hasn't been identified asks for ID
		while(deviceID == -1) {

			// Asks for the connected bluetooth's id
			USART_puts(USART1, BL_CMD_ASK_FOR_IDENTIFICATION);

			//Keeps sending infr packages until it pairs
			infraPair();

			deviceID = listenBluetooth();
			Delayms(100);

			//to when it exits the loop
			isPaired = 1;

			//Careful with the watchdog
			TM_WATCHDOG_Reset();

		}

		//If the device is the lights, ask for the last dim state so it can continue from there
		while(lightSteps == -1 && deviceID == BL_DEVICE_LAMP)
		{
			//Command that asks for step
			USART_puts(USART1, BL_CMD_LAMP_GET_STEP);

			//See if it responds
			lightSteps = queryLightSteps();
			Delayms(100);

			//Careful with the watchdog
			TM_WATCHDOG_Reset();
		}

		//Execute once per pairing
		if(isPaired)
		{

			//Allow certain commands to work
			switch(deviceID)
			{
			case BL_DEVICE_DOOR:
				activeCommandDoor = 1;
				break;
			case BL_DEVICE_LAMP:
				activeCommandLight = 1;
				break;
			}

			//Flashes LEDS to indicate pairing is finished
			TM_DISCO_LedOn(LED_GREEN|LED_BLUE|LED_RED|LED_ORANGE);
			Delayms(500);
			TM_DISCO_LedOff(LED_GREEN|LED_BLUE|LED_RED|LED_ORANGE);
			isPaired = 0;

			//Careful with the watchdog
			TM_WATCHDOG_Reset();
		}


		/******************************************************************************************/

		// Getting accelerometer values
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);

		x = (float) Axes_Data.X;
		y = (float) Axes_Data.Y;
		z = (float) Axes_Data.Z;

		Delayms(SAMPLEPERIOD);

		// Calculating EWMA
		ex[v] = EWMA_ALPHA * x + (1.0 - EWMA_ALPHA) * fx;
		fx = ex[v];
		ey[v] = EWMA_ALPHA * y + (1.0 - EWMA_ALPHA) * fy;
		fy = ey[v];
		ez[v] = EWMA_ALPHA * z + (1.0 - EWMA_ALPHA) * fz;
		fz = ez[v];

		// Calculating variance
		vx[v] = variance(ex, 0, v + 1);
		vy[v] = variance(ey, 0, v + 1);
		vz[v] = variance(ez, 0, v + 1);

		// Calculating EWMA for variance
		vx[v] = EWMA_ALPHA * vx[v] + (1.0 - EWMA_ALPHA) * fvx;
		fvx = vx[v];
		vy[v] = EWMA_ALPHA * vy[v] + (1.0 - EWMA_ALPHA) * fvy;
		fvy = vy[v];
		vz[v] = EWMA_ALPHA * vz[v] + (1.0 - EWMA_ALPHA) * fvz;
		fvz = vz[v];

		// Filled up the arrays
		if((v + 1) < SIZE) {
			v++;
		} else {

			// Checking movement
			moving = (vx[v] > OFFSET) || (vy[v] > OFFSET) || (vz[v] > OFFSET);
			if(moving) {
				prependToLinkedList(signalX, ex[v] / ACCELEROMETER_DATA_DIVIDER);
				prependToLinkedList(signalY, ey[v] / ACCELEROMETER_DATA_DIVIDER);
				prependToLinkedList(signalZ, ez[v] / ACCELEROMETER_DATA_DIVIDER);
				count++;
			} else {
				if(count >= MIN_SAMPLES && count <= MAX_SAMPLES) {
					recognizeGesture(signalX, signalY, signalZ, count);
				}
				if(count > 0) {
					freeLinkedList(signalX);
					freeLinkedList(signalY);
					freeLinkedList(signalZ);
					count = 0;
				}
			}

			// Pushing guys left
			for(int i = 1; i < SIZE; i++) {
				ex[i - 1] = ex[i];
				ey[i - 1] = ey[i];
				ez[i - 1] = ez[i];
				vx[i - 1] = vx[i];
				vy[i - 1] = vy[i];
				vz[i - 1] = vz[i];
			}

		}

	}

}

void recognizeGesture(LinkedList *signalX, LinkedList *signalY, LinkedList *signalZ, int size) {

	// Allocating arrays for the smoothed signals
	float x[size], y[size], z[size];
	float dist;
	int klass;

	// Filling up the temporary raw signal arrays
	arrayFromLinkedList(signalX, x, size);
	arrayFromLinkedList(signalY, y, size);
	arrayFromLinkedList(signalZ, z, size);

	klass = knn(x, y, z, size, &dist);

	// Checking for NaN and long distances
	if(klass != klass) {
		return;
	}

	if(klass < 2 && dist > MAX_DISTANCE_DOOR) {
		return;
	} else if(klass >= 2 && dist > MAX_DISTANCE_LIGHT) {
		return;
	}

	if(klass == GESTURE_DOOR_OPEN) { // Door Open

		TM_DISCO_LedOn(LED_RED);
		TM_WATCHDOG_Reset(); // Gesture made, reset watchdog
		if(activeCommandDoor) { USART_puts(USART1, BL_CMD_DOOR_OPEN); }

	} else if(klass == GESTURE_DOOR_CLOSE) { // Door Close

		TM_DISCO_LedOn(LED_GREEN);
		TM_WATCHDOG_Reset(); //Gesture made, reset watchdog
		if(activeCommandDoor) { USART_puts(USART1, BL_CMD_DOOR_CLOSE); }

	} else if(klass == GESTURE_LIGHT_UP) { // Light Up

		TM_DISCO_LedOn(LED_ORANGE);
		TM_WATCHDOG_Reset(); //Gesture made, reset watchdog
		if(activeCommandLight) {

			// Walking towards zero, light all the way up taking steps of size 16
			lightSteps -= LIGHT_STEP_DELTA;

			// Don't let it underflow
			if(lightSteps < LIGHT_STEP_MIN) lightSteps = LIGHT_STEP_MIN;

			// Send command
			sendLightCommand(lightSteps);

		}

	} else if(klass == GESTURE_LIGHT_DOWN) { // Light Down

		TM_DISCO_LedOn(LED_BLUE);
		TM_WATCHDOG_Reset(); //Gesture made, reset watchdog
		if(activeCommandLight) {

			// Walking towards 128, light all the way down taking steps of size 16
			lightSteps += LIGHT_STEP_DELTA;

			// Don't let it overflow
			if(lightSteps > LIGHT_STEP_MAX) lightSteps = LIGHT_STEP_MAX;

			// Send command
			sendLightCommand(lightSteps);

		}

	}

	Delayms(100);
	TM_DISCO_LedOff(LED_GREEN | LED_RED | LED_ORANGE | LED_BLUE);

}

float variance(float *array, int begin, int end) {
	float avg = average(array, begin, end);
	float sum = 0.0;
	for(int i = begin; i < end; i++) {
		sum += pow(array[i] - avg, 2.0);
	}
	return sum / ((end - begin)) ;
}

void setup() {
	SystemInit();
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_50Hz);
	TM_DISCO_ButtonInit();
	initINFRA();
	init_USART1(9600);
	TM_WATCHDOG_Init(TM_WATCHDOG_Timeout_32s);
}

void sendLightCommand(int lightStep)
{
	char buf[8];
	sprintf(buf, BL_CMD_LAMP_STEP, lightStep);
	USART_puts(USART1, (unsigned char *) buf); // Check this out
}


/*
 * Callback used by stm32f4_discovery_audio_codec.c.
 * Refer to stm32f4_discovery_audio_codec.h for more info.
 */
void EVAL_AUDIO_TransferComplete_CallBack(uint32_t pBuffer, uint32_t Size){
	/* TODO, implement your code here */
	return;
}

/*
 * Callback used by stm324xg_eval_audio_codec.c.
 * Refer to stm324xg_eval_audio_codec.h for more info.
 */
uint16_t EVAL_AUDIO_GetSampleCallBack(void){
	/* TODO, implement your code here */
	return -1;
}
