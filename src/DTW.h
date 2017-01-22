/*
 * DTW.h
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#ifndef DTW_H_
#define DTW_H_

#include <math.h>
#include <stdio.h>
#include "defines.h"

float average(float *array, int begin, int end);
void ewma(float *array, int size, float *result);
float dtwDistance(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb);
int knn(int16_t inputX[], int16_t inputY[], int16_t inputZ[], int size);

#endif /* DTW_H_ */
