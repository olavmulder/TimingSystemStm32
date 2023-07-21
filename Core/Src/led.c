/*
 * led.c
 *
 *  Created on: Jul 20, 2023
 *      Author: olav
 */


#include "led.h"

void ButtonTask(void)
{

	static char i = 0;
	while(1)
	{

		if(button_pressed)
		{
			uint32_t start_time_ms = HAL_GetTick();
			i ^= 1;

			HAL_GPIO_WritePin(GPIOA, led_reset_Pin, i);
			//debounce
			while(HAL_GetTick() - start_time_ms < 500)
			{
				osDelay(5);
			}
			button_pressed = false;

		}
		osDelay(50);
	}
}
void LedTask(void)
{
	static char i = 0;
	while(1)
	{
		i ^= 1;
		HAL_GPIO_WritePin(GPIOA, led_timer_toggle_Pin, i);
		osDelay(1000);
	}
}
