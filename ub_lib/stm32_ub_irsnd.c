//--------------------------------------------------------------
// File     : stm32_ub_irsnd.c
// Datum    : 14.06.2013
// Version  : 1.0
// Autor    : UB
// EMail    : mc-4u(@)t-online.de
// Web      : www.mikrocontroller-4u.de
// CPU      : STM32F4
// IDE      : CooCox CoIDE 1.7.0
// Module   : IRSND, TIM, MISC
// Funktion : Infrarot-Fernbedienungs Sender (per IRSND)
// Hinweis  : Benutzt Timer2+Timer10
//            IR-Sende Dioede wird benötigt
//
//            Im File : "irsndconfig.h" wird eingestellt
//              1. Pinbelegung der Sende Diode (im Beispiel : PB8)
//              2. Benutzte Protokolle (im Beispiel : 6 standard Typen)
//              3. Timer-Nr der für das PWM benutzt wird (TIM10)
//
// IRSND    : Quelle = svn://mikrocontroller.net/irmp
//            Version : 2.3.10    Datum : 09.04.2013
//--------------------------------------------------------------


//--------------------------------------------------------------
// Includes
//--------------------------------------------------------------
#include "stm32_ub_irsnd.h"



//--------------------------------------------------------------
// interne Funktionen
//--------------------------------------------------------------
void P_IRSND_InitTIM(void);
void P_IRSND_InitNVIC(void);


//--------------------------------------------------------------
// init vom IRSND-Modul
//--------------------------------------------------------------
void UB_IRSND_Init(void)
{
  // Init vom Timer
  P_IRSND_InitTIM();
  // Init vom Interrupt
  P_IRSND_InitNVIC();
  // init vom IRSND
  irsnd_init();
}



//--------------------------------------------------------------
// Senden von IR-Daten
// Wichtig !! : Die Struktur "IRMP_DATA" muss
//              vor dem Aufruf gefüllt werden
//
// Die Daten der Struktur "IRMP_DATA" :
//   .protocol = Nr. vom IR-Protokol  [1..35]
//   .adress  = Adresse vom IR-Device [0...65535]
//   .command = Commando-Nr           [0...65535]
//   .flags   = Flag-Bits             [0...255]
//                Bit0 = Tastenwiederholung
//--------------------------------------------------------------
void UB_IRSND_Write(IRMP_DATA * irmp_data_p)
{
  // sende Daten und warte bis senden fertig
  irsnd_send_data(irmp_data_p, TRUE);
}




//--------------------------------------------------------------
// interne Funktion
// init vom Timer
//--------------------------------------------------------------
void P_IRSND_InitTIM(void)
{
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;

  // Clock enable
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  // Timer Init
  TIM_TimeBaseStructure.TIM_Period = IRSND_TIM2_PERIODE;
  TIM_TimeBaseStructure.TIM_Prescaler = IRSND_TIM2_PRESCALE;
  TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

  // Timer Interrupt Enable
  TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

  // Timer enable
  TIM_Cmd(TIM2, ENABLE);
}

//--------------------------------------------------------------
// interne Funktion
// init vom Interrupt
//--------------------------------------------------------------
void P_IRSND_InitNVIC(void)
{
  NVIC_InitTypeDef NVIC_InitStructure;

  // NVIC konfig
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x0F;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x0F;
  NVIC_Init(&NVIC_InitStructure);
}


//--------------------------------------------------------------
// Interrupt
// wird bei Timer2 Interrupt aufgerufen
//--------------------------------------------------------------
void TIM2_IRQHandler(void)
{
  TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

  // IRSND ISR aufrufen
  irsnd_ISR();
}
