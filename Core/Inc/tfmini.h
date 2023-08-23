/*
 * tfmini.h
 *
 *  Created on: Aug 18, 2023
 *      Author: olav
 */

#ifndef INC_TFMINI_H_
#define INC_TFMINI_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "data.h"


extern UART_HandleTypeDef huart2;

void UARTDataTask();
void StartContinuesMeasurement();
void StopMeasurement();

#endif /* INC_TFMINI_H_ */
