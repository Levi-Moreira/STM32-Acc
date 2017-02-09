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
#include "TestSeries.h"
#include "DTW.h"
#include "LinkedList.h"
#include "serial.h"
#include "time.h"

#define SIZE 10
#define OFFSET 1000

void setup() {
	SystemInit();
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_50Hz);
	TM_DISCO_ButtonInit();
}

void testTimeOfDTW() {
	int ms[121];
	for(int l = 0; l <= 120; l++) {
		TM_DELAY_SetTime(0);
		//		dtwDistance(ts1, ts1, ts1, l+50, ts2, ts2, ts2, l+50, (l + 50) * DTW_WINDOW_RATIO);
		knn(ts1, ts2, ts3, l + 30);
		ms[l] = TM_DELAY_Time();
	}
	ms[0] += 0; // Just to avoid the unused warning
}

float variance(float *array, int size) {
	float avg = average(array, 0, size);
	float sum = 0.0;
	for(int i = 0; i < size; i++) {
		sum += pow(array[i] - avg, 2.0);
	}
	return sum / size;
}

int main(void) {

	setup();

	init_USART1(9600);

	//	testTimeOfDTW();

	int count = 0;

	// Raw signals
	LinkedList *signalX = newLinkedList();
	LinkedList *signalY = newLinkedList();
	LinkedList *signalZ = newLinkedList();

	TM_LIS302DL_LIS3DSH_t Axes_Data;

	float valuesx[SIZE], valuesy[SIZE], valuesz[SIZE];
	float ex[SIZE], ey[SIZE], ez[SIZE];
	float vx, vy, vz;
	int moving = 0;

	int v = 0;


	// Waiting for blue button to start sampling
//	while(!TM_DISCO_ButtonPressed());

//	TM_DISCO_LedOn(LED_RED | LED_GREEN | LED_ORANGE | LED_BLUE);

	while(1) {

		Delayms(SAMPLEPERIOD);

		// Adding accelerometer values
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		//		prependToLinkedList(signalX, (float) Axes_Data.X / ACCELEROMETER_DATA_DIVIDER);
		//		prependToLinkedList(signalY, (float) Axes_Data.Y / ACCELEROMETER_DATA_DIVIDER);
		//		prependToLinkedList(signalZ, (float) Axes_Data.Z / ACCELEROMETER_DATA_DIVIDER);
		//		count++;

		valuesx[v] = (float) Axes_Data.X;
		valuesy[v] = (float) Axes_Data.Y;
		valuesz[v] = (float) Axes_Data.Z;

		if((v + 1) == SIZE) {

			ewma(valuesx, SIZE, ex);
			ewma(valuesy, SIZE, ey);
			ewma(valuesz, SIZE, ez);

			vx = variance(ex, SIZE);
			vy = variance(ey, SIZE);
			vz = variance(ex, SIZE);

			moving = (vx > OFFSET) || (vy > OFFSET) || (vz > OFFSET);

			if(moving) {
				TM_DISCO_LedOn(LED_GREEN);
			} else {
				TM_DISCO_LedOff(LED_GREEN);
			}

			for(int i = 1; i < SIZE; i++) {
				valuesx[i - 1] = valuesx[i];
				valuesy[i - 1] = valuesy[i];
				valuesz[i - 1] = valuesz[i];
			}

		} else {
			v++;
		}

	}

//	TM_DISCO_LedOff(LED_RED | LED_GREEN | LED_ORANGE | LED_BLUE);

	while(1);

	// Allocating the temporary arrays to store the raw signal
	float tempX[200];// = (float *) malloc(count * sizeof(float));
	float tempY[200];// = (float *) malloc(count * sizeof(float));
	float tempZ[200];// = (float *) malloc(count * sizeof(float));
	for(int i = 0; i < 200; i++) {
		tempX[i] = 666.666;
		tempY[i] = 666.666;
		tempZ[i] = 666.666;
	}

	// Filling up the temporary raw signal arrays
	arrayFromLinkedList(signalX, tempX, count);
	arrayFromLinkedList(signalY, tempY, count);
	arrayFromLinkedList(signalZ, tempZ, count);

	// Freeing the memory for the linked lists
	freeLinkedList(signalX);
	freeLinkedList(signalY);
	freeLinkedList(signalZ);

	// Allocating arrays for the smoothed signals
	//	float *smoothX = (float *) malloc(count * sizeof(float));
	//	float *smoothY = (float *) malloc(count * sizeof(float));
	//	float *smoothZ = (float *) malloc(count * sizeof(float));
	float smoothX[200];
	float smoothY[200];
	float smoothZ[200];
	for(int i = 0; i < 200; i++) {
		smoothX[i] = 666.666;
		smoothY[i] = 666.666;
		smoothZ[i] = 666.666;
	}

	// Calculating the smoothed values
	ewma(tempX, count, smoothX);
	ewma(tempY, count, smoothY);
	ewma(tempZ, count, smoothZ);

	double klass = knn(smoothX, smoothY, smoothZ, count);

	if(klass != klass) { //NaN
		TM_DISCO_LedOff(LED_GREEN | LED_RED | LED_ORANGE | LED_BLUE);
		while(1);
	} else {
		if(klass < 0) {
			TM_DISCO_LedOn(LED_GREEN | LED_RED | LED_ORANGE | LED_BLUE);
			klass *= -1;
		}
		if(klass == 0) { // Door Open
			TM_DISCO_LedOn(LED_RED);
			USART_puts(USART1, "0");
		} else if(klass == 1) { // Door Close
			TM_DISCO_LedOn(LED_GREEN);
			USART_puts(USART1, "1");
		} else if(klass == 2) { // Light Up
			TM_DISCO_LedOn(LED_ORANGE);
			USART_puts(USART1, "2");
		} else if(klass == 3) { // Light Down
			TM_DISCO_LedOn(LED_BLUE);
			USART_puts(USART1, "3");
		}
	}

	while(1);

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
