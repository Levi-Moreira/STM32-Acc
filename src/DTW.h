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

void printArray(double *array, int size);
double average(double *array, int begin, int end);
void ewma(double *array, int size, double *result);
float dtwDistance(double *ax, double *ay, double *az, int sa, double *bx, double *by, double *bz, int sb);
int knn(int16_t inputX[], int16_t inputY[], int16_t inputZ[], int size);

#endif /* DTW_H_ */
