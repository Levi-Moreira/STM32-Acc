#ifndef TM_DEFINES_H
#define TM_DEFINES_H

//tell compiler which board is being used
#define TM_DISCO_STM32F4_DISCOVERY

//sample period in ms
#define SAMPLEPERIOD 20
//total amount of samples
#define SAMPLEAMOUNT 148

//sample total time in ms
#define SAMPLETOTALTIME SAMPLEAMOUNT * SAMPLEPERIOD

// The amount to divide the accelerometer data by in order to turn the data into doubles
#define ACCELEROMETER_DATA_DIVIDER 100.0

#define EWMA_ALPHA 0.3
#define DTW_WINDOW_RATIO 0.6
#define NUMBER_OF_GESTURES 4

#define SIZE 6
#define AVG_SIZE 6
#define OFFSET 3600//5000//2500 //1300 //1000

#define MAX_DISTANCE_LIGHT 30
#define MAX_DISTANCE_DOOR 18

#define MIN_SAMPLES 15
#define MAX_SAMPLES 40

#endif
