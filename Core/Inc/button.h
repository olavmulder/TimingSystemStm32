/*
 * button.h
 *
 *  Created on: Sep 4, 2023
 *      Author: olav
 */

#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "atlete.h"

#define UP	GPIO_PIN_6
#define DOWN GPIO_PIN_5
#define LEFT GPIO_PIN_7


uint16_t GetPushedButton();
void SetButton(uint16_t num);
uint8_t GetMenuIndicator();

#endif /* INC_BUTTON_H_ */
