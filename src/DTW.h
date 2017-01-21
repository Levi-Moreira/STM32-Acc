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
int16_t average(int16_t *array, int begin, int end);
void ewma(int16_t *array, int size, int16_t *result);
double dtwDistance(int16_t *ax, int16_t *ay, int16_t *az, int sa, int16_t *bx, int16_t *by, int16_t *bz, int sb);
int knn(int16_t *inputX, int16_t *inputY, int16_t *inputZ, int size);

#endif /* DTW_H_ */
