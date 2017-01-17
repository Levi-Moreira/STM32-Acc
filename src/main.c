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
#include "tm_stm32f4_usart.h"


int main(void)
{


	u_int8_t pressed = 1, done = 1;
	u_int16_t time = 0;
	int16_t signal[SAMPLEAMOUNT];

	TM_LIS302DL_LIS3DSH_t Axes_Data;

	SystemInit();

	//Initialize delays
	TM_DELAY_Init();

	//Initialize LEDs
	TM_DISCO_LedInit();

	//start accelerometer
	TM_LIS302DL_LIS3DSH_Init(TM_LIS3DSH_Sensitivity_2G, TM_LIS3DSH_Filter_50Hz);

	//start button
	TM_DISCO_ButtonInit();

	TM_USART_Init(USART1, TM_USART_PinsPack_1, 9600);

	TM_USART_Puts(USART1, "Hello world\n\r");

	//turn leds blue and orange to indicate the disc is mounted
	TM_DISCO_LedOn(LED_BLUE | LED_ORANGE);

	//wait for blue button press
	while(pressed)
		{
			if(TM_DISCO_ButtonPressed())
			{
				pressed = 0;
			}
		}

	//turn off blue and orange leds
	TM_DISCO_LedOff(LED_BLUE | LED_ORANGE);

	//turn leds red and green to tell sampling is about to start
	TM_DISCO_LedOn(LED_RED | LED_GREEN);
	int i = 0;
	while (done) {
		/* Read axes data from initialized accelerometer */
		TM_LIS302DL_LIS3DSH_ReadAxes(&Axes_Data);

		//save data to array
		signal[i] = Axes_Data.X;
		signal[i+1] = Axes_Data.Y;
		signal[i+2] = Axes_Data.Z;
		i++;

		//wait for the next sampling period
		Delayms(SAMPLEPERIOD);

		//increase the timer
		time += SAMPLEPERIOD;

		//if total sampling time is reached, leave loop
		if(time>=SAMPLETOTALTIME)
		{
			done = 0;
		}
	}

	//sample finishes
	TM_DISCO_LedOff(LED_RED | LED_GREEN);

	//wait for the blue button to save file
	pressed = 1;
	while(pressed)
	{
			if(TM_DISCO_ButtonPressed())
			{
				pressed = 0;
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
