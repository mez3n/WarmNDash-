/*
 * ProtectedUART.c
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */
#include "ProtectedUART.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"


xSemaphoreHandle xUART0_Mutex;

void UART0_Init_Sync(void){
    xUART0_Mutex = xSemaphoreCreateRecursiveMutex();
    UART0_Init();
}

void UART0_SendByte_Sync(uint8 data){
    xSemaphoreTakeRecursive(xUART0_Mutex, portMAX_DELAY);
    UART0_SendByte(data);
    xSemaphoreGiveRecursive(xUART0_Mutex);

}

uint8 UART0_ReceiveByte_Sync(void){
    xSemaphoreTakeRecursive(xUART0_Mutex, portMAX_DELAY);
    uint8 data =UART0_ReceiveByte();
    xSemaphoreGiveRecursive(xUART0_Mutex);
    return data;
}

void UART0_SendString_Sync(const uint8 *pData){
    xSemaphoreTakeRecursive(xUART0_Mutex, portMAX_DELAY);
    UART0_SendString(pData);
    xSemaphoreGiveRecursive(xUART0_Mutex);
}

void UART0_SendInteger_Sync(sint64 sNumber){
    xSemaphoreTakeRecursive(xUART0_Mutex, portMAX_DELAY);
    UART0_SendInteger(sNumber);
    xSemaphoreGiveRecursive(xUART0_Mutex);
}


void UART0_Lock(){
    xSemaphoreTakeRecursive(xUART0_Mutex, portMAX_DELAY);
}
void UART0_Unlock(){
    xSemaphoreGiveRecursive(xUART0_Mutex);
}

