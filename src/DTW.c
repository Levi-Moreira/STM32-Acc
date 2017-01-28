/*
 * DTW.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "DTW.h"

float min(float a, float b) {
	return a < b ? a : b;
}

float max(float a, float b) {
	return a > b ? a : b;
}

float average(float *array, int begin, int end) {
	float sum = 0;
	int i;
	for(i = begin; i < end; i++) {
		sum += array[i];
	}
	return sum / (float) end - begin;
}

void ewma(float *array, int size, float *result) {

	int s = size < 6 ? size : 6;
	float forecasted = average(array, 0, s);
	float smoothed = 0;

	int i;

	for (i = 1; i <= size; i++) {
		smoothed = EWMA_ALPHA * array[i - 1] + (1.0 - EWMA_ALPHA) * forecasted;
		forecasted = smoothed;
		result[i - 1] = smoothed;
	}

}

float dtwDistance(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int window) {

	float acc[sa][sb];
	float dist;
	int maxi, mini;
	window = max(window, abs(sa - sb));

	// Temp
	for (int i = 0; i < sa; i++) {
		for (int j = 0; j < sb; j++) {
			acc[i][j] = INFINITY;
		}
	}

	acc[0][0] = pow(ax[0] - bx[0], 2.0) + pow(ay[0] - by[0], 2.0) + pow(az[0] - bz[0], 2.0);

	// Row 0
	mini = min(window, sb);
	for (int i = 1; i < mini; i++) {
		dist = pow(ax[0] - bx[i], 2.0) + pow(ay[0] - by[i], 2.0) + pow(az[0] - bz[i], 2.0);
		acc[0][i] = acc[0][i - 1] + dist;
	}

	// Column 0
	mini = min(window, sa);
	for (int i = 1; i < mini + 1; i++) {
		dist = pow(ax[i] - bx[0], 2.0) + pow(ay[i] - by[0], 2.0) + pow(az[i] - bz[0], 2.0);
		acc[i][0] = acc[i - 1][0] + dist;
	}

	// Accumlated distance - Remaining
	float m;
	for (int i = 1; i < sa; i++) {
		mini = max(1, i - window);
		maxi = min(sb, i + window);
		for (int j = mini; j < maxi; j++) {
			dist = pow(ax[i] - bx[j], 2.0) + pow(ay[i] - by[j], 2.0) + pow(az[i] - bz[j], 2.0);
			m = min(
					min(acc[i - 1][j],
							acc[i][j - 1]),
							acc[i - 1][j - 1]);
			acc[i][j] = m + dist;
		}
	}

	return sqrt(acc[sa - 1][sb - 1]);

}

float minArray(float *array, int begin, int end) {
    float min = array[begin];
    for (int i = begin + 1; i < end; i++) {
        if(array[i] < min) { min = array[i]; }
    }
    return min;
}

float maxArray(float *array, int begin, int end) {
    double max = array[begin];
    for (int i = begin + 1; i < end; i++) {
        if(array[i] > max) { max = array[i]; }
    }
    return max;
}

float LBKeogh(float *x, int sx, float *y, int sy, int r) {

    double sum = 0;
    int li, mi;
    double lowerBound, upperBound;

    for (int i = 0; i < sx; i++) {

        li = (i - r) >= 0 ? (i - r) : 0;
        mi = (i + r) <= sy ? (i + r) : sy;

        lowerBound = minArray(y, li, mi);
        upperBound = maxArray(y, li, mi);

        if(x[i] > upperBound) {
            sum += pow(x[i] - upperBound, 2);
        } else if(x[i] < lowerBound) {
            sum += pow(x[i] - lowerBound, 2);
        }

    }

    return sqrt(sum);
}

int knn(int16_t inputX[], int16_t inputY[], int16_t inputZ[], int size) {
	//	double distanceO = dtwDistance(smooth2Ox, smooth2Oy, smooth2Oz, 148, inputX, inputY, inputZ, size);
	//	double distanceL = dtwDistance(smooth2Lx, smooth2Ly, smooth2Lz, 148, inputX, inputY, inputZ, size);
	//    return distanceO < distanceL ? 0 : 1;
	return 0;
}
