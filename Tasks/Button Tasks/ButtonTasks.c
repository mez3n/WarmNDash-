/*
 * ButtonTasks.c
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"



/* MCAL includes. */
#include "gpio.h"
#include "tm4c123gh6pm_registers.h"

#include "ButtonTasks.h"
#include "LedsTasks.h"


QueueHandle_t xRIS_REG_Queue;

void Buttons_SetupHarware(){
    xRIS_REG_Queue = xQueueCreate(10, sizeof(uint32));   // 32 bits as the tiva c is a 32 bit micro controller
    // may need to increase q size

    GPIO_Init_PF0_PF4_Interrupt();
    GPIO_SetPortFCallBack(PortF_IntCB_SendQ);

}


void PortF_IntCB_SendQ(){
    uint32 PortF_RIS_REG_Value = GPIO_PORTF_RIS_REG;
    GPIO_PORTF_ICR_REG =~(0x0);
    BaseType_t xHigherPriorityTaskWoken = pdFALSE;
    xQueueSendFromISR(xRIS_REG_Queue,&PortF_RIS_REG_Value,&xHigherPriorityTaskWoken);
    portYIELD_FROM_ISR( xHigherPriorityTaskWoken );
}

void vProcessButtonPressTask(){
    uint32 PortF_RIS_REG_Value;
    uint8 bit;
    uint8 bitPos;
    for(;;){
        xQueueReceive(xRIS_REG_Queue,&PortF_RIS_REG_Value, portMAX_DELAY);
        for(bitPos=0;bitPos<=6;bitPos++){
            bit= (PortF_RIS_REG_Value>>bitPos) & (1<<0);
            if(bit==1){
                if(bitPos==0){             // PF0
                    // first heater task
                    xSemaphoreGive(xHeater1StateBS);
                }else if(bitPos==4){        //PF4
                    xSemaphoreGive(xHeater2StateBS);
                }
            }
        }
    }
}




