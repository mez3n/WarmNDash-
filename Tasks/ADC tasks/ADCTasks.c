/*
 * ADCTasks.c
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* MCAL includes. */
#include "ADC.h"
#include "ProtectedUART.h"

#include "ADCTasks.h"
#include "LedsTasks.h"

/* FreeRTOS Binary Semaphores */
xSemaphoreHandle xAdc0ReqSemaphore;
xSemaphoreHandle xAdc0ReadSemaphore;

xSemaphoreHandle xAdc1ReqSemaphore;
xSemaphoreHandle xAdc1ReadSemaphore;



void ADC_SetupHarware(){
    ADC0_Init();
    ADC1_Init();

    AIN0_Init();
    AIN1_Init();

    ADC0_SetCallBack(ADC0_IntCB_GiveReadSem);
    ADC1_SetCallBack(ADC1_IntCB_GiveReadSem);

    xAdc0ReqSemaphore = xSemaphoreCreateBinary();
    xAdc0ReadSemaphore = xSemaphoreCreateBinary();

    xAdc1ReqSemaphore = xSemaphoreCreateBinary();
    xAdc1ReadSemaphore = xSemaphoreCreateBinary();
}


volatile void ADC0_IntCB_GiveReadSem(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xAdc0ReadSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void vRequestAdc0ReadTask(void *pvParameters)
{
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(ADC_READ_INTERVAL));
        ADC0_RequestRead();
        xSemaphoreTake(xAdc0ReqSemaphore,portMAX_DELAY);
    }
}

void vAdc0ReadTask(void *pvParameters)
{
    uint8 Temp;
    for(;;){
        xSemaphoreTake(xAdc0ReadSemaphore,portMAX_DELAY);
        uint16 uxAnalogValue=ADC0_Read_SS3();
        Temp=(uxAnalogValue*45)/4096;
        UART0_Lock();
        UART0_SendString_Sync("Temp0= ");
        UART0_SendInteger_Sync(Temp);
        UART0_SendString_Sync("\r \n");
        UART0_Unlock();
        xQueueSend( xHeater1TempQ, &Temp, portMAX_DELAY);
        xSemaphoreGive(xAdc0ReqSemaphore);
    }
}



volatile void ADC1_IntCB_GiveReadSem(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xAdc1ReadSemaphore, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void vRequestAdc1ReadTask(void *pvParameters)
{
    for(;;){
        vTaskDelay(pdMS_TO_TICKS(ADC_READ_INTERVAL));
        ADC1_RequestRead();
        xSemaphoreTake(xAdc1ReqSemaphore,portMAX_DELAY);
    }
}

void vAdc1ReadTask(void *pvParameters)
{
    uint8 Temp;
    for(;;){
        xSemaphoreTake(xAdc1ReadSemaphore,portMAX_DELAY);
        uint16 uxAnalogValue=ADC1_Read_SS3();
        Temp=(uxAnalogValue*45)/4096;
        UART0_Lock();
        UART0_SendString_Sync("Temp1= ");
        UART0_SendInteger_Sync(Temp);
        UART0_SendString_Sync("\r \n");
        UART0_Unlock();
        xQueueSend( xHeater2TempQ, &Temp, portMAX_DELAY);
        xSemaphoreGive(xAdc1ReqSemaphore);
    }
}




