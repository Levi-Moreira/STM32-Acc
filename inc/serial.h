/*
 * serial.h
 *
 *  Created on: 22 de jan de 2017
 *      Author: Alan
 */

#ifndef SERIAL_H_
#define SERIAL_H_

#define MAX_STRLEN 5 // this is the maximum string length of our string in characters

void init_USART1(uint32_t baudrate);
void USART_puts(USART_TypeDef* USARTx, volatile char *s);
int listenBluetooth(void);


#endif /* SERIAL_H_ */
