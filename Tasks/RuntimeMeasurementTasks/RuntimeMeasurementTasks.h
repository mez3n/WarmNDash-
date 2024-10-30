/*
 * RuntimeMeasurementTasks.h
 *
 *  Created on: Oct 2, 2024
 *      Author: Mazen
 */
#include "AppCfg.h"

#ifndef TASKS_RUNTIMEMEASUREMENTTASKS_RUNTIMEMEASUREMENTTASKS_H_
#define TASKS_RUNTIMEMEASUREMENTTASKS_RUNTIMEMEASUREMENTTASKS_H_

uint32 ullTasksOutTime[NUMBER_OF_TASKS+1];
uint32 ullTasksInTime[NUMBER_OF_TASKS+1];
uint32 ullTasksTotalTime[NUMBER_OF_TASKS+1];
uint32 ullTasksExecutionTime[NUMBER_OF_TASKS+1];

uint32 ullMutexTaskTakeTime[NUMBER_OF_TASKS +1];
uint32 ullMutexTaskGiveTime[NUMBER_OF_TASKS +1];
uint32 ullMutexTotalTime[NUMBER_OF_TASKS +1];

void vRunTimeMeasurementsTask(void *pvParameters);






#endif /* TASKS_RUNTIMEMEASUREMENTTASKS_RUNTIMEMEASUREMENTTASKS_H_ */
