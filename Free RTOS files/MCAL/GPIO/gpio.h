/**********************************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.h
 *
 * Description: Header file for the TM4C123GH6PM DIO driver for TivaC Built-in Buttons and LEDs
 *
 * Author: Edges for Training Team
 *
 ***********************************************************************************************/

#ifndef GPIO_H_
#define GPIO_H_

#include "std_types.h"



#define PRESSED                ((uint8)0x00)
#define RELEASED               ((uint8)0x01)


volatile void (*GPIO_PortFCallBack_Ptr)(void);


void GPIO_BuiltinButtonsLedsInit(void);

void GPIO_RedLedOn(void);
void GPIO_BlueLedOn(void);
void GPIO_GreenLedOn(void);
void GPIO_CyanLedOn(void);


void GPIO_RedLedOff(void);
void GPIO_BlueLedOff(void);
void GPIO_GreenLedOff(void);
void GPIO_AllLedsOff(void);

void GPIO_RedLedToggle(void);
void GPIO_BlueLedToggle(void);
void GPIO_GreenLedToggle(void);

uint8 GPIO_SW1GetState(void);
uint8 GPIO_SW2GetState(void);

void GPIO_SW1EdgeTriggeredInterruptInit(void);
void GPIO_SW2EdgeTriggeredInterruptInit(void);

void GPIO_Init_PF0_PF4_Interrupt(void);

void GPIO_SetPortFCallBack(volatile void (*PtrToFunc)(void));
void GPIO_PortFIntHandler();



void GPIO_ECULedsInit(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue


void GPIO_ECU_RedOn(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_GreenOn(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_YellowOn(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_BlueOn(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_CyanOn(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue

void GPIO_ECU_CyanOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_RedOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_GreenOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_YellowOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_BlueOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
void GPIO_ECU_ALLOff(void);   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue


#endif /* GPIO_H_ */
