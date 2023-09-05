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


void DisplayTask(void* pvParamters);
void DrawIndicator();
void DisplayAll();
void DisplayAtlete();
void DisplayExchangeData();
#endif /* INC_DISPLAY_H_ */
