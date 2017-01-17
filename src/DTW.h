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

void printArray(double *array, int size);
double average(double *array, int begin, int end);
void ewma(double alpha, double *array, int size, double *result);
double dtwDistance(double *x, int sizeX, double *y, int sizeY);
void knn(double *input, int size);

#endif /* DTW_H_ */
