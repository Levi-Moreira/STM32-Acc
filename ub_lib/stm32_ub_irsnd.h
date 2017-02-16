//--------------------------------------------------------------
// File     : stm32_ub_irsnd.h
//--------------------------------------------------------------

//--------------------------------------------------------------
#ifndef __STM32F4_UB_IRSND_H
#define __STM32F4_UB_IRSND_H


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"
#include "misc.h"
#include "irsnd.h"


//--------------------------------------------------------------
// Timer Einstellungen (Frequenz)
//
// Grundfrequenz = 2*APB1 (APB1=42MHz) => TIM_CLK=84MHz
// periode   : 0 bis 0xFFFF
// prescale  : 0 bis 0xFFFF
//
// Timer-Frq = TIM_CLK/(periode+1)/(vorteiler+1)
//--------------------------------------------------------------
#define  F_CPU 84000000UL  // TIM_CLK

#define  IRSND_TIM2_PERIODE  7
#define  IRSND_TIM2_PRESCALE ((F_CPU / F_INTERRUPTS)/8) - 1


//--------------------------------------------------------------
// Globale Funktionen
//--------------------------------------------------------------
void UB_IRSND_Init(void);
void UB_IRSND_Write(IRMP_DATA * irmp_data_p);



//--------------------------------------------------------------
#endif // __STM32F4_UB_IRSND_H
