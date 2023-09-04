/*
 * button.c
 *
 *  Created on: Sep 4, 2023
 *      Author: olav
 */

#include "../Inc/button.h"

#define UP	GPIO_PIN_6
#define DOWN GPIO_PIN_5

uint8_t menuIndicator = 0;
uint16_t pushedButton = 0;


inline uint8_t GetPushedButton()
{
	return pushedButton;
}

inline void SetButton(uint16_t num)
{
	pushedButton = num;
}

bool Debounce()
{
	static uint16_t state = 0;
	//debounce code from https://www.e-tinkers.com/2021/05/the-simplest-button-debounce-solution/
	state = (state << 1) | HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_5) | 0xfe00;
	return state;
}
int ReadButton()
{
	//debounce  button
	while(!Debounce())continue;
	switch(pushedButton)
		{
		case UP:
			if(menuIndicator > 0)
				menuIndicator--;
			break;
		case DOWN:
			if(menuIndicator < MENU_HIGHT-1)
				menuIndicator++;
			break;
		default:
			return -1;
			break;
		}
	pushedButton = 0;
	return 0;
}

uint8_t GetMenuIndicator()
{
	return menuIndicator;
}

