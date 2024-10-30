/*
 * ButtonTasks.h
 *
 *  Created on: Sep 25, 2024
 *      Author: Mazen
 */

#include "NVIC_driver.h"

#ifndef TASKS_BUTTON_TASKS_BUTTONTASKS_H_
#define TASKS_BUTTON_TASKS_BUTTONTASKS_H_



void Buttons_SetupHarware();
void PortF_IntCB_SendQ();
void vProcessButtonPressTask();





#endif /* TASKS_BUTTON_TASKS_BUTTONTASKS_H_ */
