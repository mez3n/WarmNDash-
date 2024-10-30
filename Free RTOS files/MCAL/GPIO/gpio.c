/**********************************************************************************************
 *
 * Module: GPIO
 *
 * File Name: GPIO.c
 *
 * Description: Source file for the TM4C123GH6PM DIO driver for TivaC Built-in Buttons and LEDs
 *
 * Author: Edges for Training Team
 *
 ***********************************************************************************************/
#include "gpio.h"
#include "tm4c123gh6pm_registers.h"
#include "NVIC_driver.h"
#include "AppCfg.h"

#define GPIO_PORTF_IRQ_NUM  (NVIC_IRQType) 30

void GPIO_BuiltinButtonsLedsInit(void)
{
    /*
     * PF0 --> SW2
     * PF1 --> Red LED
     * PF2 --> Blue LED
     * PF3 --> Green LED
     * PF4 --> SW1
     */

    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while(!(SYSCTL_PRGPIO_REG & 0x20));

    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;                       /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG    |= (1<<0);                           /* Enable changes on PF0 */
    GPIO_PORTF_AMSEL_REG &= 0xE0;                             /* Disable Analog on PF0, PF1, PF2, PF3 and PF4 */
    GPIO_PORTF_PCTL_REG  &= 0xFFF00000;                       /* Clear PMCx bits for PF0, PF1, PF2, PF3 and PF4 to use it as GPIO pins */
    GPIO_PORTF_DIR_REG   &= ~(1<<0) & ~(1<<4);                /* Configure PF0 & PF4 as input pins */
    GPIO_PORTF_DIR_REG   |= ((1<<1) | (1<<2) | (1<<3));       /* Configure PF1, PF2 & PF3 as output pins */
    GPIO_PORTF_AFSEL_REG &= 0xE0;                             /* Disable alternative function on PF0, PF1, PF2, PF3 and PF4 */
    GPIO_PORTF_PUR_REG   |= ((1<<0)|(1<<4));                  /* Enable pull-up on PF0 & PF4 */
    GPIO_PORTF_DEN_REG   |= 0x1F;                             /* Enable Digital I/O on PF0, PF1, PF2, PF3 and PF4 */
    GPIO_PORTF_DATA_REG  &= ~(1<<1) & ~(1<<2) & ~(1<<3);      /* Clear bits 1, 2 & 3 in Data register to turn off the LEDs */
}

void GPIO_RedLedOn(void)
{
    GPIO_PORTF_DATA_REG |= (1<<1);  /* Red LED ON */
}

void GPIO_BlueLedOn(void)
{
    GPIO_PORTF_DATA_REG |= (1<<2);  /* Blue LED ON */
}

void GPIO_GreenLedOn(void)
{
    GPIO_PORTF_DATA_REG |= (1<<3);  /* Green LED ON */
}

void GPIO_CyanLedOn(void){
    GPIO_BlueLedOn();
    GPIO_GreenLedOn();
}

void GPIO_RedLedOff(void)
{
    GPIO_PORTF_DATA_REG &= ~(1<<1);  /* Red LED OFF */
}

void GPIO_BlueLedOff(void)
{
    GPIO_PORTF_DATA_REG &= ~(1<<2);  /* Blue LED OFF */
}

void GPIO_GreenLedOff(void)
{
    GPIO_PORTF_DATA_REG &= ~(1<<3);  /* Green LED OFF */
}

void GPIO_AllLedsOff(void){
    GPIO_GreenLedOff();
    GPIO_BlueLedOff();
    GPIO_RedLedOff();
}
void GPIO_RedLedToggle(void)
{
    GPIO_PORTF_DATA_REG ^= (1<<1);  /* Red LED is toggled */
}

void GPIO_BlueLedToggle(void)
{
    GPIO_PORTF_DATA_REG ^= (1<<2);  /* Blue LED is toggled */
}

void GPIO_GreenLedToggle(void)
{
    GPIO_PORTF_DATA_REG ^= (1<<3);  /* Green LED is toggled */
}

uint8 GPIO_SW1GetState(void)
{
    return ((GPIO_PORTF_DATA_REG >> 4) & 0x01);
}

uint8 GPIO_SW2GetState(void)
{
    return ((GPIO_PORTF_DATA_REG >> 0) & 0x01);
}



void GPIO_SW1EdgeTriggeredInterruptInit(void)
{
    GPIO_PORTF_IS_REG    &= ~(1<<4);      /* PF4 detect edges */
    GPIO_PORTF_IBE_REG   &= ~(1<<4);      /* PF4 will detect a certain edge */
    GPIO_PORTF_IEV_REG   &= ~(1<<4);      /* PF4 will detect a falling edge */
    GPIO_PORTF_ICR_REG   |= (1<<4);       /* Clear Trigger flag for PF4 (Interrupt Flag) */
    GPIO_PORTF_IM_REG    |= (1<<4);       /* Enable Interrupt on PF4 pin */
    //    /* Set GPIO PORTF priority as 5 by set Bit number 21, 22 and 23 with value 2 */
    //    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS);
    //    NVIC_EN0_REG         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}

void GPIO_SW2EdgeTriggeredInterruptInit(void)
{
    GPIO_PORTF_IS_REG    &= ~(1<<0);      /* PF0 detect edges */
    GPIO_PORTF_IBE_REG   &= ~(1<<0);      /* PF0 will detect a certain edge */
    GPIO_PORTF_IEV_REG   &= ~(1<<0);      /* PF0 will detect a falling edge */
    GPIO_PORTF_ICR_REG   |= (1<<0);       /* Clear Trigger flag for PF0 (Interrupt Flag) */
    GPIO_PORTF_IM_REG    |= (1<<0);       /* Enable Interrupt on PF0 pin */
    //    /* Set GPIO PORTF priority as 5 by set Bit number 21, 22 and 23 with value 2 */
    //    NVIC_PRI7_REG = (NVIC_PRI7_REG & GPIO_PORTF_PRIORITY_MASK) | (GPIO_PORTF_INTERRUPT_PRIORITY<<GPIO_PORTF_PRIORITY_BITS_POS);
    //    NVIC_EN0_REG         |= 0x40000000;   /* Enable NVIC Interrupt for GPIO PORTF by set bit number 30 in EN0 Register */
}


void GPIO_Init_PF0_PF4_Interrupt(){
    /* Enable clock for PORTF and wait for clock to start */
    SYSCTL_RCGCGPIO_REG |= 0x20;
    while(!(SYSCTL_PRGPIO_REG & 0x20));


    GPIO_PORTF_LOCK_REG   = 0x4C4F434B;            /* Unlock the GPIO_PORTF_CR_REG */
    GPIO_PORTF_CR_REG    |= (1<<0);                /* Enable changes on PF0 */

    GPIO_PORTF_AMSEL_REG &= ~((1<<0)|(1<<4));      /* Disable Analog on PF0 and PF4*/
    GPIO_PORTF_PCTL_REG  &= 0xFFF0FFF0;            /* Clear PMCx bits for PF0 and PF4 to use them as GPIO pin */
    GPIO_PORTF_DIR_REG   &= ~((1<<0)|(1<<4));      /* Configure PF0 as input pin */
    GPIO_PORTF_AFSEL_REG &= ~((1<<0)|(1<<4));      /* Disable alternative function on PF0 */
    GPIO_PORTF_PUR_REG   |= (1<<0)|(1<<4);         /* Enable pull-up on PF0 */
    GPIO_PORTF_DEN_REG   |= (1<<0)|(1<<4);         /* Enable Digital I/O on PF0 */
    GPIO_PORTF_IS_REG    &= ~((1<<0)|(1<<4));      /* PF0 detect edges */
    GPIO_PORTF_IBE_REG   &= ~((1<<0)|(1<<4));      /* PF0 will detect a certain edge */
    GPIO_PORTF_IEV_REG   &= ~((1<<0)|(1<<4));      /* PF0 will detect a falling edge */
    GPIO_PORTF_ICR_REG   |= ((1<<0)|(1<<4));       /* Clear Trigger flag for PF0 (Interrupt Flag) */
    GPIO_PORTF_IM_REG    |= ((1<<0)|(1<<4));       /* Enable Interrupt on PF0 pin */
    NVIC_EnableIRQ(GPIO_PORTF_IRQ_NUM);
    NVIC_SetPriorityIRQ(GPIO_PORTF_IRQ_NUM, GPIO_PORTF_INTERRUPT_PRIORITY);
}



void GPIO_SetPortFCallBack(volatile void (*PtrToFunc)(void)){
    GPIO_PortFCallBack_Ptr=PtrToFunc;
}

void GPIO_PortFIntHandler(){
    uint8;
    if(GPIO_PortFCallBack_Ptr!=NULL_PTR){
        GPIO_PortFCallBack_Ptr();
    }
}

void GPIO_ECULedsInit(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    SYSCTL_RCGCGPIO_REG |= 0x04;
    while(!(SYSCTL_PRGPIO_REG & 0x04));

    GPIO_PORTC_AMSEL_REG &= 0x0F;
    GPIO_PORTC_PCTL_REG  &= 0x0000FFFF;
    GPIO_PORTC_DIR_REG   |= 0xF0;
    GPIO_PORTC_AFSEL_REG &= 0x0F;
    GPIO_PORTC_DEN_REG   |= 0xF0;
    GPIO_PORTC_DATA_REG  &= 0x0F;
}


void GPIO_ECU_RedOn(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  |= 0x10;
}

void GPIO_ECU_GreenOn(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  |= 0x20;
}


void GPIO_ECU_YellowOn(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  |= 0x40;
}

void GPIO_ECU_BlueOn(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  |= 0x80;
}

void GPIO_ECU_CyanOn(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  |= 0xA0;
}



void GPIO_ECU_RedOff(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  &= ~(0x10);
}

void GPIO_ECU_GreenOff(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  &= ~(0x20);
}


void GPIO_ECU_YellowOff(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  &= ~(0x40);
}

void GPIO_ECU_BlueOff(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  &= ~(0x80);
}

void GPIO_ECU_CyanOff(void)   //pins PC4,PC5,PC6,PC7 red,green,yellow,blue
{
    GPIO_PORTC_DATA_REG  &= ~(0xA0);
}

void GPIO_ECU_ALLOff(void){
    GPIO_PORTC_DATA_REG  &= ~(0xF0);
}


