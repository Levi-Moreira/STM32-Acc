#ifndef TM_DEFINES_H
#define TM_DEFINES_H

//tell compiler which board is being used
#define TM_DISCO_STM32F4_DISCOVERY

#define SAMPLEPERIOD 20 // Sample period in miliseconds
#define ACCELEROMETER_DATA_DIVIDER 100.0 // The amount to divide the accelerometer data by in order to turn the data into doubles

#define EWMA_ALPHA 0.3 // A parameter required for the EWMA
#define NUMBER_OF_GESTURES 4

#define SIZE 6 // The size of the values to take in consideration to calculate the variances in motion detection
#define AVG_SIZE 6 // The size of the array which is used to calculate the first average necessary in EWMA
#define OFFSET 3500 // The variance threshold for motion detection

#define MAX_DISTANCE_LIGHT 30 // The threshold for the DTW distance of a light gesture
#define MAX_DISTANCE_DOOR 22 // The threshold for the DTW distance of a door gesture

#define MIN_SAMPLES 15 // The minimum amout of samples in a gesture
#define MAX_SAMPLES 40 // The maximum amount of samples in a gesture

// Gestures
#define GESTURE_DOOR_OPEN 0
#define GESTURE_DOOR_CLOSE 1
#define GESTURE_LIGHT_UP 2
#define GESTURE_LIGHT_DOWN 3

// The amount to add or subtract to the light steps
#define LIGHT_STEP_DELTA 16
#define LIGHT_STEP_MIN 1
#define LIGHT_STEP_MAX 128

// Selected devices
#define BL_DEVICE_DOOR 1
#define BL_DEVICE_LAMP 2

#endif
