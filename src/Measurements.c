/*
 * Measurements.c
 *
 *  Created on: 5 de mar de 2017
 *      Author: Alan
 */
#include "stm32f4xx.h"
#include "stm32f4_discovery.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_disco.h"
#include "Measurements.h"
#include "DTW.h"
#include "TestSeries.h"

void testTimeOfDTW() {
	int ms[121];
	float dist;
	for(int l = 0; l <= 120; l++) {
		TM_DELAY_SetTime(0);
		dtwDistance(ts1, ts1, ts1, l+50, ts2, ts2, ts2, l+50);
		knn(ts1, ts2, ts3, l + 30, &dist);
		ms[l] = TM_DELAY_Time();
	}
	ms[0] += 0; // Just to avoid the unused warning
}
