/*
 * AppCfg.h
 *
 *  Created on: Sep 24, 2024
 *      Author: Mazen
 */

#include "NVIC_driver.h"

#ifndef APPCFG_H_
#define APPCFG_H_


#define NUMBER_OF_TASKS                                      (uint8)11
#define NUMBER_OF_MUTEXES                                    (uint8)1
#define ADC0_INT_PRIORITY                      (NVIC_IRQPriorityType)5
#define ADC1_INT_PRIORITY                      (NVIC_IRQPriorityType)5
#define GPIO_PORTF_INTERRUPT_PRIORITY          (NVIC_IRQPriorityType)6
#define EEPROM_IRQ_PRIORITY                    (NVIC_IRQPriorityType)7
#define NUMBER_OF_ERRORS_TO_READ                              (uint8)100
#define NUMBER_OF_ERRORS_TO_WRITE                             (uint8)100
#define ADC_READ_INTERVAL                                         500
#define RUNTIME_MEASUREMENTS_TASK_PERIODICITY                     10000
//#define READ_ERRORS_MODE                                     (uint8)(0)




#endif /* APPCFG_H_ */
