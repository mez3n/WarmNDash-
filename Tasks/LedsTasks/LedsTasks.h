/*
 * LedsTasks.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "NVIC_driver.h"




#ifndef TASKS_LEDSTASKS_LEDSTASKS_H_
#define TASKS_LEDSTASKS_LEDSTASKS_H_


xSemaphoreHandle xHeater1StateBS;
xSemaphoreHandle xHeater2StateBS;

QueueHandle_t xHeater1TempQ;
QueueHandle_t xHeater2TempQ;




typedef enum
{
OFF=0U,
LOW=1U,
MEDIUM=2U,
HIGH=3U,
}Heater_State;


typedef enum
{
OFF_TEMP=0U,
LOW_TEMP=25U,
MEDIUM_TEMP=30U,
HIGH_TEMP=35U
}Heater_Temp;



void Leds_SetupHarware();
void vLeds_ChangeState1Task(); //controlled by the buttons
void vLeds_ChangeTemp1Task();  //controlled by the temp


void vLeds_ChangeState2Task(); //controlled by the buttons
void vLeds_ChangeTemp2Task();  //controlled by the temp








#endif /* TASKS_LEDSTASKS_LEDSTASKS_H_ */
