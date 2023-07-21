/*
 * display.h
 *
 *  Created on: Jul 19, 2023
 *      Author: olav
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "stm32f1xx_hal.h"
#include "ssd1306/ssd1306.h"
#include "cmsis_os.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

typedef enum _type_runner
{
	INCOMMING_RUNNER, OUTGOING_RUNNER
}Type_Runner;

void DisplayTask(void* pvParamters);
void DisplayAll();
void DisplayAtlete(Type_Runner type);
int DisplayTime(char* timeString, double time);

#endif /* INC_DISPLAY_H_ */
