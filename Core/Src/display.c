/*
 * display.c
 *  Created on: Jul 19, 2023
 *      Author: Olav
 */

#include "../Inc/display.h"

#define CLEARANCE 10
#define MULTI_INDEX 10


void DisplayTask(void *parameter)
{
	//const uint8_t hz = 10;
	size_t hz = *(size_t*)parameter;
	while(1)
	{
		if(GetPushedButton())
		{
			ReadButton();
		}
		DisplayAll();
		//show i on display
		ssd1306_UpdateScreen();
		osDelay((int)(1000 / hz));
	}
}

void DisplayAll()
{
	DisplayAtlete();
	DisplayExchangeData();
	DrawIndicator();
}
//need to be done
void DrawIndicator()
{
	uint8_t menuIndicator = GetMenuIndicator();
	for(uint8_t i = 0; i < MENU_HIGHT; i++)
	{
		ssd1306_SetCursor(0, i * MULTI_INDEX);
		if( i == menuIndicator)
			ssd1306_WriteString("|", Font_7x10 , Black);
		else
			ssd1306_WriteString(" ", Font_7x10 , Black);
	}
}
void DisplayExchangeData()
{
	const uint8_t position = 30;
	char str[3][20] = {
			"Exchange at: ",
			"Take off at: ",
			"Call at: "
	};

	for(uint8_t i = 0; i < sizeof(str) / (sizeof(char)*20); i++)
	{

		ssd1306_SetCursor(CLEARANCE,position+(MULTI_INDEX*i));
		ssd1306_WriteString(&str[i][0], Font_7x10 , Black);
	}
}
void DisplayAtlete()
{
	//GetAtletes:
	const uint8_t position = 0;

	char string[50];
	char name[2][20] =
	{
			"in: name",
			"out: name",
	};
	for(uint8_t i = 0; i < 2;i++)
	{
		strcpy(string, name[i]);
		ssd1306_SetCursor(CLEARANCE, position+(i*MULTI_INDEX));
		ssd1306_WriteString(&name[i][0], Font_7x10 , Black);
	}
}


