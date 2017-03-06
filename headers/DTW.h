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

/**
 * Returns the average of the numbers from an array
 * starting from position begin until the position end
 * */
float average(float *array, int begin, int end);

/**
 * Calculates the 3D DTW Distance of the given arrays
 * */
float dtwDistance(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb);

/**
 * Returns the class to which the given arrays (signals) belongs
 * and also stores the distance of that on the pointer dist
 * */
int knn(float inputX[], float inputY[], float inputZ[], int size, float *dist);

#endif /* DTW_H_ */
