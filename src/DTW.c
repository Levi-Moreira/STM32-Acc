/*
 * DTW.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "DTW.h"

void printArray(double *array, int size) {
    int i;
    for (i = 0; i < size; i++) {
        printf("%lf, ", array[i]);
    }
}

void printMatrix(double *matrix, int rows, int columns) {
    int i, j;
    for (i = 0; i < rows; i++) {
        for (j = 0; j < columns; j++) {
            printf("%.2lf ", *(matrix + (i * columns) + j));
        }
        printf("\n");
    }
}

double average(double *array, int begin, int end) {
    double sum = 0.0;
    int i;
    for(i = begin; i < end; i++) {
        sum += array[i];
    }
    return sum / (double) end - begin;
}

double min(double a, double b, double c) {
    if(a < b) {
        return a < c ? a : c;
    }
    return b < c ? b : c;
}

void ewma(double alpha, double *array, int size, double *result) {

    int s = size < 6 ? size : 6;
    double forecasted = average(array, 0, s);
    double smoothed = 0.0;

    int i;

    for (i = 1; i <= size; i++) {
        smoothed = alpha * array[i - 1] + (1 - alpha) * forecasted;
        forecasted = smoothed;
        result[i - 1] = smoothed;
    }

}

double dtwDistance(double *x, int sizeX, double *y, int sizeY) {

    int sX = sizeX / 3;
    int sY = sizeY / 3;
    int k, l;

    double acc[sY][sX];
    double dist;

    acc[0][0] = pow(x[0] - y[0], 2.0) + pow(x[1] - y[1], 2.0) + pow(x[2] - y[2], 2.0);;

    // Accumulated distance - Row 0
    for (int i = 1; i < sX; i++) {
        k = i * 3;
        dist = pow(x[k] - y[0], 2.0) + pow(x[k + 1] - y[1], 2.0) + pow(x[k + 2] - y[2], 2.0);
        acc[0][i] = acc[0][i - 1] + dist;
    }

    // Accumulated distance - Row 0
    for (int i = 1; i < sY; i++) {
        k = i * 3;
        dist = pow(x[0] - y[k], 2.0) + pow(x[1] - y[k + 1], 2.0) + pow(x[2] - y[k + 2], 2.0);
        acc[i][0] = acc[i - 1][0] + dist;
    }

    // Accumlated distance - Remaining
    double m;
    for (int i = 1; i < sY; i++) {
        k = i * 3;
        for (int j = 1; j < sX; j++) {
            l = j * 3;
            dist = pow(x[l] - y[k], 2.0) + pow(x[l + 1] - y[k + 1], 2.0) + pow(x[l + 2] - y[k + 2], 2.0);
            m = min(acc[i - 1][j - 1],
                    acc[i - 1][j],
                    acc[i][j - 1]);
            acc[i][j] = m + dist;
        }
    }

    return sqrt(acc[sY - 1][sX - 1]);

}

void knn(double *input, int size) {

//    double minDistance = (double) INT_MAX;
//    NSString *minName;
//    double distance;
//
//    NSArray *gestures = [Gesture all];
//
//    for (Gesture *gesture in gestures) {
//
//        NSArray *array = (NSArray *) [NSKeyedUnarchiver unarchiveObjectWithData:gesture.signal];
//        double signal[array.count];
//
//        for (int i = 0; i < array.count; i++) {
//            signal[i] = [[array objectAtIndex:i] doubleValue];
//        }
//
//        distance = dtwDistance(signal, (int) array.count, input, size);
//
//        if(distance < minDistance) {
//            minDistance = distance;
//            minName = gesture.name;
//        }
//
//    }
//
//    return minName;

}
