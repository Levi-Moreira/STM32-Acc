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
#include <stdlib.h>
#include "defines.h"

float max(float a, float b);
float average(float *array, int begin, int end);
void ewma(float *array, int size, float *result);
float dtwDistance(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int window);
float LBKeogh(float *x, int sx, float *y, int sy, int r);
int knn(float inputX[], float inputY[], float inputZ[], int size);

#endif /* DTW_H_ */
