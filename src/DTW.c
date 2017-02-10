/*
 * DTW.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "DTW.h"

// Door Open
float doorOpenX[29] = {-2.74866652, -2.82106662, -2.96774673, -3.2474227, -3.49119592, -3.65883708, -3.914186, -4.26393032, -4.62275124, -4.70592594, -4.48814821, -4.1377039, -4.10839272, -4.06987476, -4.05191231, -3.81433868, -3.40203714, -3.06842589, -2.88889813, -2.57122874, -2.18086004, -1.83560205, -1.51292145, -0.897045016, -0.471931517, -0.0903520584, 0.329753548, 0.68382746, 0.775679231};
float doorOpenY[29] = {-1.98033345, -2.10623336, -2.02636337, -1.95845437, -2.02191806, -1.95534265, -2.01373982, -2.08761787, -2.16033244, -2.17823267, -2.00476289, -1.69733405, -1.49713385, -1.50699365, -1.3218956, -0.994326949, -0.600028872, -0.27902022, 0.0386858359, 0.207080096, 0.501956105, 0.798369288, 1.04485846, 1.21440089, 1.26108062, 1.30575645, 1.38502955, 1.28152072, 1.08006454};
float doorOpenZ[29] = {10.1113329, 10.0389328, 9.90425301, 9.83397675, 9.90178394, 9.8712492, 9.82887459, 9.70021248, 9.59214878, 9.67850399, 9.687953, 9.44856739, 9.50899696, 9.49729824, 9.59110928, 9.76477623, 9.94334316, 10.0353403, 10.0517387, 10.0212173, 10.0448523, 10.2713966, 10.4389772, 10.3972845, 10.4280987, 10.6026688, 10.6258678, 10.5821075, 10.6504755};

// Door Close
float doorCloseX[43] = {0.624833345, 0.455383331, 0.387768328, 0.463437825, 0.5794065, 1.16758454, 2.14330912, 2.95231652, 3.50962162, 3.82173514, 4.03721476, 4.02005053, 3.58503532, 2.85452461, 2.3761673, 2.09831715, 1.63082206, 0.895575464, -0.0570971668, -0.921968043, -1.34137762, -1.82696438, -2.523875, -3.14371252, -3.47259879, -3.66381931, -4.09767342, -4.68037128, -5.23225975, -5.48058176, -5.29740715, -5.1661849, -5.29932928, -5.37753057, -5.20727158, -5.01609039, -5.01726341, -4.98808432, -4.77865887, -4.30206108, -3.79144263, -3.58100986, -3.48470688};
float doorCloseY[43] = {-1.82716668, -2.02301669, -2.05811167, -2.00767827, -1.96937478, -1.36356235, -0.660493612, -0.0813455358, 0.210058123, 0.420040697, 0.55802846, 0.615619898, 0.622933924, 0.583053768, 0.591137648, 0.836796343, 1.14675748, 1.16273022, 0.861911178, 0.69933784, 0.768536508, 0.735975564, 0.368182898, -0.075271979, -0.394690394, -0.37228328, -0.332598299, -0.784818828, -0.942373157, -1.13966119, -1.20876288, -1.27513397, -1.53759384, -1.7663157, -1.91442096, -1.83209467, -1.92746627, -2.01822639, -2.00375843, -1.76563096, -1.62294161, -1.6040591, -1.57884133};
float doorCloseZ[43] = {10.0303335, 10.0092335, 9.97646332, 9.92952442, 10.0166674, 10.1946669, 10.3612671, 10.5588875, 10.7752209, 10.6506548, 10.3324585, 10.2807207, 10.4755049, 10.5248537, 10.3013973, 10.3909779, 10.4206848, 10.1534796, 9.72943592, 9.7746048, 10.0702238, 10.0611563, 10.0458097, 10.2120667, 9.84544659, 9.54081249, 9.69656849, 9.6405983, 9.39741898, 9.53019333, 9.71013546, 9.87209511, 10.1504669, 10.1953268, 9.97772884, 9.75041008, 9.63928699, 9.489501, 9.46865082, 9.52005577, 9.74503899, 10.0075274, 10.1792688};

// Light Up
float lightUpX[27] = {-1.15983343, -0.976883411, -0.944818377, -1.14437282, -1.42806101, -1.74964273, -1.87574995, -1.83802497, -1.6796174, -1.58373213, -1.58261251, -1.50082874, -1.35358012, -1.20850611, -1.09495425, -0.895467997, -0.719827592, -0.569879293, -0.500915527, -0.39564088, -0.12694861, 0.0791359767, 0.175395191, 0.197776631, 0.165443644, 0.0528105535, -0.0500326082};
float lightUpY[27] = {-0.842666626, -0.877866626, -0.881506622, -0.929054618, -1.00433826, -1.08103681, -1.06872571, -1.02710795, -0.89597553, -0.840182841, -0.885128021, -1.05458963, -1.10421276, -1.11494899, -1.14346433, -1.19342506, -1.27039754, -1.50127828, -1.72889483, -1.85222638, -2.13655853, -2.32359099, -2.53551364, -2.81585956, -3.10810161, -3.45367122, -3.86056972};
float lightUpZ[27] = {11.7701664, 11.2601166, 11.5420818, 12.2164574, 13.0605202, 13.7743645, 14.2590551, 14.2533388, 14.015337, 13.8007355, 13.5455151, 13.1148605, 12.7384024, 12.5678816, 12.3555174, 11.8558617, 11.335103, 10.8145723, 10.3032007, 9.7412405, 8.93986797, 7.98890734, 7.21823502, 6.5107646, 6.00053501, 5.70937443, 5.41856194};

// Light Down
float lightDownX[39] = {-0.154500008, -0.219150007, -0.234405011, -0.248083502, -0.209658444, -0.167760909, -0.105432637, -0.139802843, -0.154861987, -0.0934033915, -0.0383823738, -0.0838676617, -0.160707369, -0.187495157, -0.176246613, -0.066372633, -0.0074608447, 0.00977740902, -0.0621558167, -0.0435090736, -0.0484563522, -0.0939194486, -0.0777436122, 0.185579479, 0.411905646, 0.366333961, 0.250433773, 0.370303631, 0.640212536, 0.673148751, 0.723204136, 0.713242888, 0.685270011, 0.659689009, 0.785782337, 0.817047656, 0.838933349, 0.914253354, 0.879977345};
float lightDownY[39] = {-7.41149998, -7.58804989, -7.55863476, -7.50504446, -7.37453127, -7.18117189, -7.00082016, -6.88057423, -6.63740206, -6.37718153, -6.23102713, -6.1017189, -5.99620342, -5.80234241, -5.60963964, -5.38474798, -5.30232382, -5.1726265, -5.12083864, -5.05458689, -4.93321085, -4.84524775, -4.73867321, -4.56807137, -4.36765003, -4.28735495, -4.17714834, -3.89000392, -3.54800272, -3.37460184, -3.24122143, -3.06685495, -2.95079851, -2.83655882, -2.62159109, -2.53711367, -2.46597958, -2.41918564, -2.39242983};
float lightDownZ[39] = {-5.6826663, -5.77186632, -5.88230658, -5.76761436, -5.54933023, -5.34553099, -5.22387171, -5.08471012, -4.98729706, -4.87110806, -4.8167758, -4.77574301, -4.86702013, -5.01791382, -5.18953991, -5.23767805, -5.57137442, -6.07496214, -6.61347342, -7.08943129, -7.4856019, -7.91892147, -8.14724541, -8.34307194, -8.70815086, -9.38370514, -9.69759369, -9.66531563, -9.80772114, -9.97640514, -10.1184835, -10.2149382, -10.267457, -10.4032202, -10.5402536, -10.7561779, -10.8443241, -11.0860271, -11.4982185};

float min(float a, float b) {
	return a < b ? a : b;
}

float max(float a, float b) {
	return a > b ? a : b;
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

float average(float *array, int begin, int end) {
	float sum = 0;
	int i;
	for(i = begin; i < end; i++) {
		sum += array[i];
	}
	return sum / (float) (end - begin);
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

double dtwDistance1(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int window) {

	float acc[sb][sa];
	float dist;

	acc[0][0] = pow(ax[0] - bx[0], 2.0) + pow(ay[0] - by[0], 2.0) + pow(az[0] - bz[0], 2.0);

	// Accumulated distance - Row 0
	for (int i = 1; i < sa; i++) {
		dist = pow(ax[i] - bx[0], 2.0) + pow(ay[i] - by[0], 2.0) + pow(az[i] - bz[0], 2.0);
		acc[0][i] = acc[0][i - 1] + dist;
	}

	// Accumulated distance - Row 0
	for (int i = 1; i < sb; i++) {
		dist = pow(ax[0] - bx[i], 2.0) + pow(ay[0] - by[i], 2.0) + pow(az[0] - bz[i], 2.0);
		acc[i][0] = acc[i - 1][0] + dist;
	}

	// Accumlated distance - Remaining
	float m;
	for (int i = 1; i < sb; i++) {
		for (int j = 1; j < sa; j++) {
			dist = pow(ax[j] - bx[i], 2.0) + pow(ay[j] - by[i], 2.0) + pow(az[j] - bz[i], 2.0);
			m = min(min(acc[i - 1][j - 1],
					acc[i - 1][j]),
					acc[i][j - 1]);
			acc[i][j] = m + dist;
		}
	}

	return sqrt(acc[sb - 1][sa - 1]);

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

float LBKeogh3D(float *ax, float *ay, float *az, int sa, float *bx, float *by, float *bz, int sb, int r) {
	float lx = LBKeogh(ax, sa, bx, sb, r);
	float ly = LBKeogh(ay, sa, by, sb, r);
	float lz = LBKeogh(az, sa, bz, sb, r);
	return lx + ly + lz;
}

int knn(float inputX[], float inputY[], float inputZ[], int size) {

	int answer;
	float distance = INFINITY;
	float minDistance = INFINITY;
	int lbr = 30;

	float* pointersX[NUMBER_OF_GESTURES] = {doorOpenX, doorCloseX, lightUpX, lightDownX};
	float* pointersY[NUMBER_OF_GESTURES] = {doorOpenY, doorCloseY, lightUpY, lightDownY};
	float* pointersZ[NUMBER_OF_GESTURES] = {doorOpenZ, doorCloseZ, lightUpZ, lightDownZ};

	int sizes[NUMBER_OF_GESTURES] = {29, 43, 27, 39};
	int window = 4; // Does not matter for DTW1

	for(int i = 0; i < NUMBER_OF_GESTURES; i++) {
		if(LBKeogh3D(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], lbr) < minDistance) {
			distance = dtwDistance1(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], window);
			if(distance < minDistance) {
				minDistance = distance;
				answer = i;
			}
		}
	}

	// Checking for NaN
	if(minDistance != minDistance) {
		return minDistance;
	}

	// Negative if the distance is infinity
	return answer * (minDistance == INFINITY ? -1 : 1);

}
