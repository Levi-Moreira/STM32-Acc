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
double average(int16_t *array, int begin, int end);
void ewma(int16_t *array, int size, double *result);
double dtwDistance(double *x, int sizeX, double *y, int sizeY);
int knn(double *input, int size);

#endif /* DTW_H_ */
