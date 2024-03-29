/*
 * button.c
 *
 *  Created on: Sep 4, 2023
 *      Author: olav
 */

#include "../Inc/button.h"

uint16_t pushedButton = 0;

bool Debounce(uint16_t pin)
{
	static uint16_t state = 0;
	//debounce code from https://www.e-tinkers.com/2021/05/the-simplest-button-debounce-solution/
	state = (state << 1) | HAL_GPIO_ReadPin(GPIOA, pin) | 0xfe000;
	return state;
}

uint16_t GetPushedButton()
{
	if(pushedButton)
	{
		while(!Debounce(pushedButton))continue;
		uint16_t temp = pushedButton;
		pushedButton = 0;
		return temp;
	}
	return 0;
}

inline void SetButton(uint16_t num)
{
	pushedButton = num;
}




