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
#include "atlete.h"

enum _displayState
{
	MENU, Option1, Option2, Option3,
	Option4, Option5, Option6
};
typedef enum _displayState DISPLAY_STATE;

void DisplayTask(void* pvParamters);
void UpdateIndicator(int8_t *indicator, uint16_t pin, uint8_t min, uint8_t max);
void DrawMenu(int8_t *indicator, uint16_t pin);
void DrawIndicator(int8_t indicator);
void ShowAthletes(uint16_t pin);

#endif /* INC_DISPLAY_H_ */
