/*
 * ErrorRepTasks.c
 *
 *  Created on: Sep 30, 2024
 *      Author: Mazen
 */
/* Kernel includes. */
#include <Tasks/EEPROMRepTask/EEPROMRepTask.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* MCAL includes. */
#include "ProtectedUART.h"

#include "AppCfg.h"

xSemaphoreHandle xEEPROM_Wait_BS;
void EEPROMRepTaskSetupHardware(){
    xEEPROM_Wait_BS=xSemaphoreCreateBinary();
    xError_ReportQueue=xQueueCreate(20, sizeof(uint8)*256);
    EEPROM_Init();
    EEPROM_SetWaitCB(EEPROMRepTask_Wait_CB);
    EEPROM_SetInterruptCB(EEPROMRepTask_Int_CB);
}
void EEPROMRepTask_Int_CB(){
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xSemaphoreGiveFromISR(xEEPROM_Wait_BS, &xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}
void EEPROMRepTask_Wait_CB(){
    xSemaphoreTake(xEEPROM_Wait_BS,portMAX_DELAY);
}
void vEEPROMRepTaskReport(){
    uint8 counter =0;
    for(;;){
        char Str[256];
        xQueueReceive(xError_ReportQueue,&Str, portMAX_DELAY);
        if(counter<NUMBER_OF_ERRORS_TO_WRITE)
        {
            EEPROM_Write(Str);
            counter++;
        }
    }
}
void vEEPROMRepTaskRead(){
    uint8 counter=0;
    for(;;){
        while(counter<NUMBER_OF_ERRORS_TO_READ){
            counter++;
            char  Str[256];
            EEPROM_Read(Str);
            UART0_SendString_Sync((const uint8 *)Str);
            UART0_SendString_Sync("\r \n");
        }
        vTaskDelay(portMAX_DELAY);
    }
}
