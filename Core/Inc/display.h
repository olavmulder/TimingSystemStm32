/*
 * display.h
 *
 *  Created on: Jul 19, 2023
 *      Author: olav
 */

#ifndef INC_DISPLAY_H_
#define INC_DISPLAY_H_

#include "ssd1306/ssd1306.h"
#include "storage.h"
#include "button.h"
#include "menu.h"

enum _displayState
{
	MENU
};
typedef enum _displayState DISPLAY_STATE;


void DisplayTask(void* pvParamters);
int8_t UpdateMenuIndicator(uint16_t pin);
void DrawMenu(int8_t menuIndicator);
void DrawIndicator(int8_t menuIndicator);

#endif /* INC_DISPLAY_H_ */
