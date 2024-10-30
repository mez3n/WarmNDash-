/*
 * RuntimeMeasurementTasks.c
 *
 *  Created on: Oct 2, 2024
 *      Author: Mazen
 */

/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

#include "RuntimeMeasurementTasks.h"
#include "ProtectedUART.h"
#include "GPTM.h"

extern TaskHandle_t xTask1Handle;
extern TaskHandle_t xTask2Handle;
extern TaskHandle_t xTask3Handle;
extern TaskHandle_t xTask4Handle;
extern TaskHandle_t xTask5Handle;
extern TaskHandle_t xTask6Handle;
extern TaskHandle_t xTask7Handle;
extern TaskHandle_t xTask8Handle;
extern TaskHandle_t xTask9Handle;
extern TaskHandle_t xTask10Handle;
extern TaskHandle_t xTask11Handle;



uint8 * GetTaskName(uint8_t TaskNumber)
{
    switch(TaskNumber)
    {
    case 1:
        return "RunTimeMeasurementsTask";
    case 2:
        return "RequestAdc0ReadTask";
    case 3:
        return "Adc0ReadTask";
    case 4:
        return "RequestAdc1ReadTask";
    case 5:
        return "Adc1ReadTask";
    case 6:
        return "ProcessButtonPressTask";
    case 7:
        return "Leds_ChangeState1Task";
    case 8:
        return "Leds_ChangeTemp1Task";
    case 9:
        return "Leds_ChangeState2Task";
    case 10:
        return "Leds_ChangeTemp2Task";
    case 11:
        return "vEEPROMRepTaskReport";
    default:
        return NULL;
    }
}




static void PrintTaskMeasurements(uint8 TaskNumber){
    UART0_SendString_Sync(GetTaskName(TaskNumber));
    UART0_SendString_Sync(" execution time is: ");
    UART0_SendInteger_Sync(ullTasksTotalTime[TaskNumber] / 10);
    UART0_SendString_Sync(" msec \r\n");
}

static void PrintMutexMeasurements(uint8 TaskNumber){
    UART0_SendString_Sync(GetTaskName(TaskNumber));
    UART0_SendString_Sync(" UART Mutex time is: ");
    UART0_SendInteger_Sync(ullMutexTotalTime[TaskNumber]/ 10);
    UART0_SendString_Sync(" msec \r\n");
}


void vRunTimeMeasurementsTask(void *pvParameters)
{
    TickType_t xLastWakeTime = xTaskGetTickCount();
    for (;;)
    {
        uint8 ucCounter, ucCPU_Load;
        uint32 ullTotalTasksTime = 0;
        vTaskDelayUntil(&xLastWakeTime, RUNTIME_MEASUREMENTS_TASK_PERIODICITY);
        UART0_Lock();
        for(ucCounter = 1; ucCounter <= NUMBER_OF_TASKS; ucCounter++)
        {
            ullTotalTasksTime += ullTasksTotalTime[ucCounter];
            PrintTaskMeasurements(ucCounter);
        }
        for(ucCounter = 1; ucCounter <= NUMBER_OF_TASKS; ucCounter++)
        {
            PrintMutexMeasurements(ucCounter);
        }
        ucCPU_Load = (ullTotalTasksTime * 100) /  GPTM_WTimer0Read();
        UART0_SendString_Sync("CPU Load is ");
        UART0_SendInteger_Sync(ucCPU_Load);
        UART0_SendString_Sync("% \r\n");
        UART0_Unlock();

    }
}
