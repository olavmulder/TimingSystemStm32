/*
 * display.c
 *  Created on: Jul 19, 2023
 *      Author: Olav
 */

#include "../Inc/display.h"


void DisplayTask(void *parameter)
{
	//const uint8_t hz = 10;
	size_t hz = *(size_t*)parameter;
	while(1)
	{
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
}

void DisplayExchangeData()
{
	const uint8_t position = 30;
	char str[3][20] = {
			"Exchange at: ",
			"Take off at: ",
			"Call at: "
	};
	const uint8_t multiIndex = 10;
	for(uint8_t i = 0; i < sizeof(str) / (sizeof(char)*20); i++)
	{

		ssd1306_SetCursor(2,position+(multiIndex*i));
		ssd1306_WriteString(&str[i][0], Font_7x10 , Black);
	}
}
void DisplayAtlete()
{
	//GetAtletes:
	const uint8_t position = 0;
	const uint8_t multiIndex = 10;

	char string[50];
	char name[2][20] =
	{
			"in: name",
			"out: name",
	};
	for(uint8_t i = 0; i < 2;i++)
	{
		strcpy(string, name[i]);
		ssd1306_SetCursor(2, position+(i*multiIndex));
		ssd1306_WriteString(&name[i][0], Font_7x10 , Black);
	}
}


