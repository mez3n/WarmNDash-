/*
 * LedsTasks.c
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */

#include "EEPROMRepTask.h"
#include "gpio.h"

#include "LedsTasks.h"
#include "ProtectedUART.h"
#include "GPTM.h"
Heater_State Heater1State=OFF;
Heater_State Heater2State=OFF;

static Heater_Temp GetHeaterIdealTemp(Heater_State * HeaterStatePtr ){
    Heater_Temp Temp;
    if(*HeaterStatePtr==OFF){
        Temp=OFF_TEMP;
    }else if(*HeaterStatePtr==LOW)
    {
        Temp=LOW_TEMP;
    }else if(*HeaterStatePtr==MEDIUM)
    {
        Temp=MEDIUM_TEMP;
    }else if(*HeaterStatePtr==HIGH)
    {
        Temp=HIGH_TEMP;
    }
    return Temp;
}


static void SetHeater1Intensity(sint8 TempDiff){
    if(TempDiff<=0){ //off
        GPIO_AllLedsOff();
    }else if(TempDiff<2 && Heater2State==OFF ) //low intensity
    {
        //do nothing
    }else if(TempDiff<5) //low intensity
    {
        GPIO_AllLedsOff();
        GPIO_GreenLedOn();
    }else if(TempDiff<10) //medium intensity
    {
        GPIO_AllLedsOff();
        GPIO_BlueLedOn();
    }else if(TempDiff>=10) //high intensity
    {
        GPIO_AllLedsOff();
        GPIO_CyanLedOn();
    }

}

static void SetHeater2Intensity(sint8 TempDiff){
    if(TempDiff<=0){ //off
        GPIO_ECU_ALLOff();
    }
    else if(TempDiff<2 && Heater2State==OFF ) //low intensity
    {
        //do nothing
    }
    else if(TempDiff<5) //low intensity
    {
        GPIO_ECU_ALLOff();
        GPIO_ECU_GreenOn();
    }else if(TempDiff<10) //medium intensity
    {
        GPIO_ECU_ALLOff();
        GPIO_ECU_BlueOn();
    }else if(TempDiff>=10) //high intensity
    {
        GPIO_ECU_ALLOff();
        GPIO_ECU_CyanOn();
    }

}


static void ReportHeater1State(){
    char Str[256]="\0";
    if(Heater1State==OFF){
        concatStringToString(Str,"Heater1 State Changed to OFF at time stamp = ");
    }else if(Heater1State==LOW){
        concatStringToString(Str,"Heater1 State Changed to LOW at time stamp = ");
    }else if(Heater1State==MEDIUM){
        concatStringToString(Str,"Heater1 State Changed to MEDIUM at time stamp = ");
    }else if(Heater1State==HIGH){
        concatStringToString(Str,"Heater1 State Changed to HIGH at time stamp = ");
    }

    concatStringToInt(Str,GPTM_WTimer0Read()/10);
    xQueueSend(xError_ReportQueue, Str, portMAX_DELAY);
}


static void ReportHeater2State(){
    char Str[256]="\0";
    if(Heater2State==OFF){
        concatStringToString(Str,"Heater2 State Changed to OFF at time stamp = ");
    }else if(Heater2State==LOW){
        concatStringToString(Str,"Heater2 State Changed to LOW at time stamp = ");
    }else if(Heater2State==MEDIUM){
        concatStringToString(Str,"Heater2 State Changed to MEDIUM at time stamp = ");
    }else if(Heater2State==HIGH){
        concatStringToString(Str,"Heater2 State Changed to HIGH at time stamp = ");
    }
    concatStringToInt(Str,GPTM_WTimer0Read()/10);
    xQueueSend(xError_ReportQueue, Str, portMAX_DELAY);
}


void Leds_SetupHarware(){
    xHeater1StateBS=xSemaphoreCreateBinary();
    xHeater1TempQ = xQueueCreate(10, sizeof(uint8));

    xHeater2StateBS=xSemaphoreCreateBinary();
    xHeater2TempQ = xQueueCreate(10, sizeof(uint8));

    GPIO_BuiltinButtonsLedsInit();
    GPIO_ECULedsInit();
}

void vLeds_ChangeState1Task(){
    for(;;){
        xSemaphoreTake(xHeater1StateBS, portMAX_DELAY);
        Heater1State++;
        if(Heater1State>HIGH){
            Heater1State=OFF;
        }
        ReportHeater1State();
        UART0_Lock();
        UART0_SendString_Sync("Heater1 State=");
        UART0_SendInteger_Sync(Heater1State);
        UART0_SendString_Sync("\r \n");
        UART0_Unlock();
    }
}

void vLeds_ChangeTemp1Task(){
    Heater_Temp Temp;
    Heater_Temp IdealTemp;
    for(;;){
        xQueueReceive( xHeater1TempQ, &Temp, portMAX_DELAY);
        if(Temp>40||Temp<5){
            char Str[256] ="invalid temp reading from Sensor 0 at time stamp =  ";
            concatStringToInt(Str,GPTM_WTimer0Read()/10);
            GPIO_AllLedsOff();
            GPIO_RedLedOn();
            xQueueSend(xError_ReportQueue, Str, portMAX_DELAY);
        }else{
            IdealTemp=GetHeaterIdealTemp(&Heater1State);
            SetHeater1Intensity((sint8)IdealTemp-(sint8)Temp);
        }
    }
}



void vLeds_ChangeState2Task(){
    for(;;){
        xSemaphoreTake(xHeater2StateBS, portMAX_DELAY);
        Heater2State++;
        if(Heater2State>HIGH){
            Heater2State=OFF;
        }
        ReportHeater2State();
        UART0_Lock();
        UART0_SendString_Sync("Heater2 State=");
        UART0_SendInteger_Sync(Heater2State);
        UART0_SendString_Sync("\r \n");
        UART0_Unlock();
    }
}
void vLeds_ChangeTemp2Task(){
    Heater_Temp Temp;
    Heater_Temp IdealTemp;
    for(;;){
        xQueueReceive(xHeater2TempQ, &Temp, portMAX_DELAY);
        if(Temp>40||Temp<5){
            char Str[256] ="invalid temp reading from Sensor 1 at time stamp =  ";
            concatStringToInt(Str,GPTM_WTimer0Read()/10);
            GPIO_ECU_ALLOff();
            GPIO_ECU_RedOn();
            xQueueSend(xError_ReportQueue, Str, portMAX_DELAY);
        }else{
            IdealTemp=GetHeaterIdealTemp(&Heater2State);
            SetHeater2Intensity((sint8)IdealTemp-(sint8)Temp);
        }
    }
}
