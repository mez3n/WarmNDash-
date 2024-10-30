/* Kernel includes. */
#include "EEPROMRepTask.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/* MCAL includes. */
#include "ProtectedUART.h"
#include "GPTM.h"
#include "gpio.h"

/* Task includes. */
#include "ADCTasks.h"
#include "ButtonTasks.h"
#include "LedsTasks.h"
#include "RuntimeMeasurementTasks.h"

#include "AppCfg.h"
/* The HW setup function */
static void prvSetupHardware( void );
/* FreeRTOS tasks */


/* Used to hold the handle of tasks */
TaskHandle_t xTask1Handle;
TaskHandle_t xTask2Handle;
TaskHandle_t xTask3Handle;
TaskHandle_t xTask4Handle;
TaskHandle_t xTask5Handle;
TaskHandle_t xTask6Handle;
TaskHandle_t xTask7Handle;
TaskHandle_t xTask8Handle;
TaskHandle_t xTask9Handle;
TaskHandle_t xTask10Handle;
TaskHandle_t xTask11Handle;


int main()
{
    /* Setup the hardware for use with the Tiva C board. */
    prvSetupHardware();



    /* Create Tasks here */
    xTaskCreate(vRunTimeMeasurementsTask, "Run time", 256, NULL, 5, xTask1Handle);


    xTaskCreate(vRequestAdc0ReadTask, "RequestAdc0ReadTask", 256, NULL, 4, &xTask2Handle);
    xTaskCreate(vAdc0ReadTask, "Adc0ReadTask", 256, NULL, 3, &xTask3Handle);

    xTaskCreate(vRequestAdc1ReadTask, "RequestAdc1ReadTask", 256, NULL, 4, &xTask4Handle);
    xTaskCreate(vAdc1ReadTask, "Adc1ReadTask", 256, NULL, 3, &xTask5Handle);

    xTaskCreate(vProcessButtonPressTask, "ProcessButtonPressTask", 256, NULL, 2, &xTask6Handle);

    xTaskCreate(vLeds_ChangeState1Task, "vLeds_ChangeState1Task", 256, NULL, 1, &xTask7Handle);
    xTaskCreate(vLeds_ChangeTemp1Task, "vLeds_ChangeTemp1Task", 256, NULL, 0, &xTask8Handle);

    xTaskCreate(vLeds_ChangeState2Task, "vLeds_ChangeState2Task", 256, NULL, 1, &xTask9Handle);
    xTaskCreate(vLeds_ChangeTemp2Task, "vLeds_ChangeTemp2Task", 256, NULL, 0, &xTask10Handle);

    xTaskCreate(vEEPROMRepTaskReport, "vEEPROMRepTaskReport", 256, NULL, 0, &xTask11Handle);
#if defined(READ_ERRORS_MODE)
    xTaskCreate(vEEPROMRepTaskRead, "vEEPROMRepTaskRead", 256, NULL, 5, NULL);
#endif



    vTaskSetApplicationTaskTag( xTask1Handle, ( TaskHookFunction_t ) 1 );
    vTaskSetApplicationTaskTag( xTask2Handle, ( TaskHookFunction_t ) 2 );
    vTaskSetApplicationTaskTag( xTask3Handle, ( TaskHookFunction_t ) 3 );
    vTaskSetApplicationTaskTag( xTask4Handle, ( TaskHookFunction_t ) 4 );
    vTaskSetApplicationTaskTag( xTask5Handle, ( TaskHookFunction_t ) 5 );
    vTaskSetApplicationTaskTag( xTask6Handle, ( TaskHookFunction_t ) 6 );
    vTaskSetApplicationTaskTag( xTask7Handle, ( TaskHookFunction_t ) 7 );
    vTaskSetApplicationTaskTag( xTask8Handle, ( TaskHookFunction_t ) 8 );
    vTaskSetApplicationTaskTag( xTask9Handle, ( TaskHookFunction_t ) 9 );
    vTaskSetApplicationTaskTag( xTask10Handle, ( TaskHookFunction_t ) 10 );
    vTaskSetApplicationTaskTag( xTask11Handle, ( TaskHookFunction_t ) 11 );


    /* Now all the tasks have been started - start the scheduler.

    NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
    The processor MUST be in supervisor mode when vTaskStartScheduler is
    called.  The demo applications included in the FreeRTOS.org download switch
    to supervisor mode prior to main being called.  If you are not using one of
    these demo application projects then ensure Supervisor mode is used here. */
    vTaskStartScheduler();

    /* Should never reach here!  If you do then there was not enough heap
    available for the idle task to be created. */
    for (;;);

}


static void prvSetupHardware( void )
{
    /* Place here any needed HW initialization such as GPIO, UART, etc.  */
    GPTM_WTimer0Init();
    UART0_Init_Sync();
    ADC_SetupHarware();
    Buttons_SetupHarware();
    Leds_SetupHarware();
    EEPROMRepTaskSetupHardware();
}




/*-----------------------------------------------------------*/
