/*
 * ErrorRepTasks.h
 *
 *  Created on: Sep 30, 2024
 *      Author: Mazen
 */


/* Kernel includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
/* MCAL includes. */
#include "EEPROM.h"

#ifndef TASKS_ERRORREPTASKS_ERRORREPTASKS_H_
#define TASKS_ERRORREPTASKS_ERRORREPTASKS_H_

QueueHandle_t xError_ReportQueue;


void EEPROMRepTaskSetupHardware();
void EEPROMRepTask_Int_CB();
void EEPROMRepTask_Wait_CB();
void vEEPROMRepTaskReport();
void vEEPROMRepTaskRead();







#endif /* TASKS_ERRORREPTASKS_ERRORREPTASKS_H_ */
