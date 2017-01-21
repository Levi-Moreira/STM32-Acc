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

void setup() {
	SystemInit();
	TM_DELAY_Init();
	TM_DISCO_LedInit();
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_8G, TM_LIS3DSH_Filter_50Hz);
	TM_DISCO_ButtonInit();
}



int main(void)
{

	u_int16_t time = 0;

	int16_t signalX[SAMPLEAMOUNT];
	int16_t signalY[SAMPLEAMOUNT];
	int16_t signalZ[SAMPLEAMOUNT];

	TM_LIS302DL_LIS3DSH_t Axes_Data;

	setup();

	TM_DISCO_LedOn(LED_BLUE | LED_ORANGE);

	// Waiting for blue button to start sampling
	while(!TM_DISCO_ButtonPressed());

	TM_DISCO_LedOff(LED_BLUE | LED_ORANGE);
	TM_DISCO_LedOn(LED_RED | LED_GREEN);

	int i = 0;
	do {

		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);
		signalX[i] = Axes_Data.X;
		signalY[i] = Axes_Data.Y;
		signalZ[i++] = Axes_Data.Z;

		Delayms(SAMPLEPERIOD);
		time += SAMPLEPERIOD;

	} while(time < SAMPLETOTALTIME);

	TM_DISCO_LedOff(LED_RED | LED_GREEN);

	int16_t smoothX[SAMPLEAMOUNT];
	int16_t smoothY[SAMPLEAMOUNT];
	int16_t smoothZ[SAMPLEAMOUNT];

	ewma(signalX, SAMPLEAMOUNT, smoothX);
	ewma(signalY, SAMPLEAMOUNT, smoothY);
	ewma(signalZ, SAMPLEAMOUNT, smoothZ);

	int gesture = knn(smoothX, smoothY, smoothZ, SAMPLEAMOUNT);

	while(1) {
		TM_DISCO_LedOn(gesture == 0 ? LED_ORANGE : LED_BLUE);
	}

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
