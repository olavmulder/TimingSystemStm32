/*
 * display.c
 *  Created on: Jul 19, 2023
 *      Author: Olav
 */

#include "../Inc/display.h"

#define FONT_HIGHT 10
static DISPLAY_STATE displayState = MENU;

void DrawIndicator(int8_t indicator)
{
	for(uint8_t i = 0; i < AMOUNT_OPTIONS; i++)
	{
		ssd1306_SetCursor(0, i * FONT_HIGHT);
		if( i == indicator)
			ssd1306_WriteString("|", Font_7x10 , Black);
		else
			ssd1306_WriteString(" ", Font_7x10 , Black);
	}
}


void DisplayTask(void *parameter)
{
	//const uint8_t hz = 10;
	size_t hz = *(size_t*)parameter;
	static int8_t menuIndicator = 0;

	while(1)
	{
		uint16_t pin;
		if((pin = GetPushedButton()))
		{
			//read pushed button pin
			//update display state
			if(pin == LEFT && displayState == MENU)
				displayState = menuIndicator+1;
			else if(pin == LEFT)
				displayState =  MENU;


			switch(displayState)
			{
				case MENU:
					DrawMenu(&menuIndicator, pin);
					break;
				case Option1:
					ShowAthletes(pin);
					break;
				default:
					break;
			}
		}
		//show on display
		ssd1306_UpdateScreen();
		osDelay((int)(1000 / hz));
	}
}


void UpdateIndicator(int8_t *indicator, uint16_t pin, uint8_t min, uint8_t max)
{
	if(pin == UP)
	{
		*indicator-=1;
		*indicator = (*indicator < min) ?  max : *indicator;
	}
	else if(pin == DOWN)
	{
		*indicator +=1;
		*indicator = (*indicator > max) ? min : *indicator;
	}
}

void DrawMenu(int8_t *menuIndicator, uint16_t pin)
{
	const uint8_t position = 0;
	const uint8_t margin = 4;
	//clear screen
	ssd1306_Fill(Black);
	UpdateIndicator(menuIndicator, pin, Show_Athletes, Get_Exchangedata);
	DrawIndicator(*menuIndicator);
	for(uint8_t i = 0; i < AMOUNT_OPTIONS;i++)
	{
		ssd1306_SetCursor(margin, i * FONT_HIGHT);
		ssd1306_WriteString(enumToString(i), Font_7x10 , Black);
	}
}




void ShowAthletes(uint16_t pin)
{
	static int8_t athletesIndicator = 0;

	const uint8_t margin = 4;
	ssd1306_Fill(Black);
	uint8_t amount = GetAmountAtletes();
	UpdateIndicator(&athletesIndicator, pin, 0, amount);
	DrawIndicator(0);

	for(uint8_t i = (uint8_t)athletesIndicator;
		 (i < athletesIndicator+AMOUNT_OPTIONS) && (i < amount) ;
		i++)
	{
		ssd1306_SetCursor(margin,(i-athletesIndicator)* FONT_HIGHT);
		char *name = GetAtleteNameByNumber(i);
		if(name != NULL)
			ssd1306_WriteString(name, Font_7x10 , Black);
	}
}

