/*
 * infra.c
 *
 *  Created on: 16 de fev de 2017
 *      Author: Levi
 */


#include "infra.h"
#include "stm32_ub_irsnd.h"

//will send an specified infrared package
void sendInfraData(IRMP_DATA irData)
{
	int i;
	for(i = 0; i<1000; i++)
	{
	   if(i%200==0)
		   UB_IRSND_Write(&irData);
	   Delayms(1);
	}
}



void initINFRA(void)
{
	UB_IRSND_Init();
}

int infraPair(void)
{
	IRMP_DATA myInfraData;

	myInfraData.protocol=IRMP_NEC_PROTOCOL;
	myInfraData.address=0x00FF;
	myInfraData.command=0xffff;
	myInfraData.flags=0;

	sendInfraData(myInfraData);

	return 1;
}
