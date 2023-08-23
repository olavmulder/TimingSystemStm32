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
#include <assert.h>

#define ISDataValid(x) ((x[4] == 0x01) ? 1 : 0) //byte 5 indicates if data is valid

extern UART_HandleTypeDef huart2;

void UARTDataTask();
void StartContinuesMeasurement();
void StopMeasurement();
int HandleData(char* data);
int CRCCheck(char *data);
void test_lazer();
#endif /* INC_LAZER_H_ */
