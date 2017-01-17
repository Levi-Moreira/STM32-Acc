#ifndef TM_DEFINES_H
#define TM_DEFINES_H

//tell compiler which board is being used
#define TM_DISCO_STM32F4_DISCOVERY

//sample period in ms
#define SAMPLEPERIOD 20
//total amount of samples
#define SAMPLEAMOUNT 100

//sample total time in ms
#define SAMPLETOTALTIME SAMPLEAMOUNT*SAMPLEPERIOD

/* Put your global defines for all libraries here used in your project */

#endif
