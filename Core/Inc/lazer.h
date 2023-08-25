/*
 * tfmini.h
 *
 *  Created on: Aug 18, 2023
 *      Author: olav
 */

#ifndef INC_LAZER_H_
#define INC_LAZER_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "data.h"
#include "fifo.h"
#include <assert.h>

#define ISDataValid(x) ((x[4] == 0x01) ? 1 : 0) //byte 5 indicates if data is valid
#define MAX_MEASUREMENT_DISTANCE 40 //30 exchange zone + 10 extra behing actual start point
#define MEASURE_FROM 5 //only measure data from 5m

extern UART_HandleTypeDef huart2;

void UARTDataTask(void* parameter);
void StartContinuesMeasurement();
void StopMeasurement();
int MeasurementDone();
double HandleData(char* data);
int CRCCheck(char *data, size_t len);
void test_lazer();

void test_makeRunningPerson();
#endif /* INC_LAZER_H_ */
