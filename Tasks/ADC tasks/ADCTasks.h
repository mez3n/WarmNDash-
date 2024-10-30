/*
 * ADCTasks.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */

#ifndef TASKS_ADC_TASKS_ADCTASKS_H_
#define TASKS_ADC_TASKS_ADCTASKS_H_

#include "std_types.h"



// ADC0 tasks
void vAdc0ReadTask(void *pvParameters);

void vRequestAdc0ReadTask(void *pvParameters);

volatile void ADC0_IntCB_GiveReadSem();

// ADC1 tasks
void vAdc1ReadTask(void *pvParameters);

void vRequestAdc1ReadTask(void *pvParameters);

volatile void ADC1_IntCB_GiveReadSem();


void ADC_SetupHarware();

#endif /* TASKS_ADC_TASKS_ADCTASKS_H_ */
