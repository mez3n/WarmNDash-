/*
 * ProtectedUART.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */


#include "uart0.h"

#ifndef UART_WRAPPER_PROTECTEDUART_H_
#define UART_WRAPPER_PROTECTEDUART_H_




void UART0_Init_Sync(void);

void UART0_SendByte_Sync(uint8 data);

uint8 UART0_ReceiveByte_Sync(void);

void UART0_SendString_Sync(const uint8 *pData);

void UART0_SendInteger_Sync(sint64 sNumber);

void UART0_Lock();
void UART0_Unlock();






#endif /* UART_WRAPPER_PROTECTEDUART_H_ */
