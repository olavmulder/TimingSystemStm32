/*
 * display.c
 *  Created on: Jul 19, 2023
 *      Author: Olav
 */

#include "../Inc/display.h"

#define FONT_HIGHT 10
static DISPLAY_STATE displayState = MENU;

void DisplayTask(void *parameter)
{
	//const uint8_t hz = 10;
	size_t hz = *(size_t*)parameter;
	while(1)
	{
		if(GetPushedButton())
		{
			//Get Display State
			//if menu
			uint16_t pin = ReadButton();
			switch(displayState)
			{
				case MENU:
					DrawMenu(UpdateMenuIndicator(pin));
					break;
				default:
					break;
			}
		}
		//show i on display
		ssd1306_UpdateScreen();
		osDelay((int)(1000 / hz));
	}
}


int8_t UpdateMenuIndicator(uint16_t pin)
{
	static int8_t menuIndicator = 0;
	if(pin == UP)
	{
		menuIndicator-=1;
		menuIndicator = (menuIndicator < Show_Athletes) ?  Get_Exchangedata : menuIndicator;
	}
	else if(pin == DOWN)
	{
		menuIndicator +=1;
		menuIndicator = (menuIndicator > Get_Exchangedata) ? Show_Athletes : menuIndicator;
	}
	return menuIndicator;
}
void DrawMenu(int8_t menuIndicator)
{
	const uint8_t position = 0;
	const uint8_t margin = 4;
	//clear screen
	ssd1306_Fill(Black);
	DrawIndicator(menuIndicator);
	for(uint8_t i = 0; i < AMOUNT_OPTIONS;i++)
	{
		ssd1306_SetCursor(margin, i * FONT_HIGHT);
		ssd1306_WriteString(enumToString(i), Font_7x10 , Black);
	}
}
//need to be done
void DrawIndicator(int8_t menuIndicator)
{
	for(uint8_t i = 0; i < AMOUNT_OPTIONS; i++)
	{
		ssd1306_SetCursor(0, i * FONT_HIGHT);
		if( i == menuIndicator)
			ssd1306_WriteString("|", Font_7x10 , Black);
		else
			ssd1306_WriteString(" ", Font_7x10 , Black);
	}
}

