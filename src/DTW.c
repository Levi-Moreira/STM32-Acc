/*
 * DTW.c
 *
 *  Created on: 17 de jan de 2017
 *      Author: Alan
 */

#include "DTW.h"

// Door Open
float doorOpenX[46] = {-1.31200004, -1.23640001, -1.33648002, -1.28653598, -1.40157521, -1.57810259, -1.89367187, -2.2885704, -2.74799919, -3.21959949, -3.6907196, -4.05350399, -4.4664526, -4.8965168, -5.34456158, -5.61019325, -5.6701355, -5.58009481, -5.30406618, -4.91284657, -4.5639925, -4.44579458, -4.77405643, -4.73383951, -4.24068785, -3.86548138, -3.85483694, -3.57138586, -2.85397005, -2.28277898, -2.20394516, -2.05276155, -0.950933099, 0.549346864, 1.77054274, 2.87137985, 3.96896601, 4.49127626, 4.51189327, 4.26532555, 3.79572797, 3.59600949, 3.15920663, 2.65544462, 2.16181135, 1.97526789};
float doorOpenY[46] = {-1.72549999, -1.71184993, -1.65429497, -1.81200647, -1.83240449, -1.74168313, -1.66317821, -1.65922475, -1.67145729, -1.68302011, -1.67611408, -1.57827985, -1.40479589, -1.33435714, -1.39304996, -1.320135, -1.2060945, -0.979266167, -0.772486329, -0.678740442, -0.409118295, -0.172382802, -0.159667954, -0.0427675657, 0.408062726, 0.651643932, 0.90915072, 1.43140554, 1.97998393, 2.06398869, 2.12579203, 2.40905428, 2.88333797, 3.17333651, 3.32233548, 3.50463486, 3.34424448, 2.94697118, 2.45887995, 1.97921598, 1.58045113, 1.19031584, 0.89322108, 0.62525475, 0.353678316, 0.127574816};
float doorOpenZ[46] = {9.95883369, 9.90818405, 9.87272835, 9.88090992, 9.94963646, 10.0997458, 10.0278215, 10.0164747, 9.96653271, 9.77557278, 9.80090046, 9.88763046, 9.99634171, 10.015439, 10.010807, 9.902565, 9.68579578, 9.69905663, 9.76233959, 9.67463779, 9.73024654, 9.67017269, 9.56212139, 9.43548489, 9.1668396, 9.00878811, 8.96715164, 9.27400589, 9.4288044, 9.44716263, 9.36101341, 9.54970932, 9.79879665, 9.89215755, 10.2755108, 10.6938572, 10.9956999, 11.5309896, 11.8156929, 11.8619852, 11.9453897, 11.7937727, 11.5916405, 11.399148, 11.2524033, 11.0326824};

// Door Close
float doorCloseX[43] = {0.624833345, 0.455383331, 0.387768328, 0.463437825, 0.5794065, 1.16758454, 2.14330912, 2.95231652, 3.50962162, 3.82173514, 4.03721476, 4.02005053, 3.58503532, 2.85452461, 2.3761673, 2.09831715, 1.63082206, 0.895575464, -0.0570971668, -0.921968043, -1.34137762, -1.82696438, -2.523875, -3.14371252, -3.47259879, -3.66381931, -4.09767342, -4.68037128, -5.23225975, -5.48058176, -5.29740715, -5.1661849, -5.29932928, -5.37753057, -5.20727158, -5.01609039, -5.01726341, -4.98808432, -4.77865887, -4.30206108, -3.79144263, -3.58100986, -3.48470688};
float doorCloseY[43] = {-1.82716668, -2.02301669, -2.05811167, -2.00767827, -1.96937478, -1.36356235, -0.660493612, -0.0813455358, 0.210058123, 0.420040697, 0.55802846, 0.615619898, 0.622933924, 0.583053768, 0.591137648, 0.836796343, 1.14675748, 1.16273022, 0.861911178, 0.69933784, 0.768536508, 0.735975564, 0.368182898, -0.075271979, -0.394690394, -0.37228328, -0.332598299, -0.784818828, -0.942373157, -1.13966119, -1.20876288, -1.27513397, -1.53759384, -1.7663157, -1.91442096, -1.83209467, -1.92746627, -2.01822639, -2.00375843, -1.76563096, -1.62294161, -1.6040591, -1.57884133};
float doorCloseZ[43] = {10.0303335, 10.0092335, 9.97646332, 9.92952442, 10.0166674, 10.1946669, 10.3612671, 10.5588875, 10.7752209, 10.6506548, 10.3324585, 10.2807207, 10.4755049, 10.5248537, 10.3013973, 10.3909779, 10.4206848, 10.1534796, 9.72943592, 9.7746048, 10.0702238, 10.0611563, 10.0458097, 10.2120667, 9.84544659, 9.54081249, 9.69656849, 9.6405983, 9.39741898, 9.53019333, 9.71013546, 9.87209511, 10.1504669, 10.1953268, 9.97772884, 9.75041008, 9.63928699, 9.489501, 9.46865082, 9.52005577, 9.74503899, 10.0075274, 10.1792688};

// Light Up
float lightUpX[27] = {-1.15983343, -0.976883411, -0.944818377, -1.14437282, -1.42806101, -1.74964273, -1.87574995, -1.83802497, -1.6796174, -1.58373213, -1.58261251, -1.50082874, -1.35358012, -1.20850611, -1.09495425, -0.895467997, -0.719827592, -0.569879293, -0.500915527, -0.39564088, -0.12694861, 0.0791359767, 0.175395191, 0.197776631, 0.165443644, 0.0528105535, -0.0500326082};
float lightUpY[27] = {-0.842666626, -0.877866626, -0.881506622, -0.929054618, -1.00433826, -1.08103681, -1.06872571, -1.02710795, -0.89597553, -0.840182841, -0.885128021, -1.05458963, -1.10421276, -1.11494899, -1.14346433, -1.19342506, -1.27039754, -1.50127828, -1.72889483, -1.85222638, -2.13655853, -2.32359099, -2.53551364, -2.81585956, -3.10810161, -3.45367122, -3.86056972};
float lightUpZ[27] = {11.7701664, 11.2601166, 11.5420818, 12.2164574, 13.0605202, 13.7743645, 14.2590551, 14.2533388, 14.015337, 13.8007355, 13.5455151, 13.1148605, 12.7384024, 12.5678816, 12.3555174, 11.8558617, 11.335103, 10.8145723, 10.3032007, 9.7412405, 8.93986797, 7.98890734, 7.21823502, 6.5107646, 6.00053501, 5.70937443, 5.41856194};

// Light Down
float lightDownX[36] = {0.358500004, 0.274949998, 0.246464998, 0.289525509, 0.454667836, 0.525267482, 0.565687239, 0.593981087, 0.493786752, 0.372650713, 0.257855505, 0.315498859, 0.610849202, 0.949594438, 0.943716109, 0.660601258, 0.354420871, 0.197094604, 0.230966225, 0.131676361, -0.0248265434, -0.0983785838, -0.0478650071, 0.0834944919, 0.0524461456, -0.167287707, -0.375101388, -0.48457098, -0.633199692, -0.803239822, -1.08126783, -1.26688755, -1.30982125, -1.24687493, -1.1638124, -1.13866866};
float lightDownY[36] = {-7.09550047, -7.2588501, -7.26819515, -7.22673655, -7.05671549, -6.94070101, -6.77849054, -6.66194344, -6.58036041, -6.5112524, -6.35487652, -6.05341339, -5.66238928, -5.20867252, -4.82507086, -4.74854946, -4.67698479, -4.40188932, -4.17632246, -3.97642565, -3.7164979, -3.40554857, -3.06488395, -2.86841869, -2.5898931, -2.47292519, -2.40604758, -2.33523321, -2.11466336, -1.99926436, -1.97848499, -1.86193955, -1.66035771, -1.53125036, -1.28487527, -1.04641271};
float lightDownZ[36] = {6.57750034, 6.54225016, 6.56557512, 6.60290241, 6.65603161, 6.50422192, 6.28695536, 6.08386898, 5.79770851, 5.20739603, 4.59017706, 4.17912388, 4.26638651, 4.43847084, 4.85292959, 5.29305077, 5.74213552, 6.44049454, 6.99534607, 7.54874229, 8.16411972, 8.73288345, 9.00801849, 9.13161278, 9.36212921, 9.9674902, 10.2892427, 10.4514694, 11.0210285, 11.5457201, 12.0090046, 12.3603029, 12.8042116, 13.0969477, 13.2898636, 13.4849043};

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

	int sizes[NUMBER_OF_GESTURES] = {46, 43, 27, 36};
	int window = 10;

	for(int i = 0; i < NUMBER_OF_GESTURES; i++) {
		//		if(LBKeogh3D(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], lbr) < minDistance) {
		distance = dtwDistance1(inputX, inputY, inputZ, size, pointersX[i], pointersY[i], pointersZ[i], sizes[i], window);
		if(distance < minDistance) {
			minDistance = distance;
			answer = i;
		}
		//		}
	}

	if(minDistance != minDistance) { //Nan
		return minDistance;
	}

	// Negative if the distance is infinity
	return answer * (minDistance == INFINITY ? -1 : 1);

}
