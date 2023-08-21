/*
 * display.c
 *
 *  Created on: Jul 19, 2023
 *      Author: olav
 */

#include "../Inc/display.h"

char atlete_incoming_name[20];
char atlete_outgoing_name[20];

/*void DisplayTask(void* pvParamters)
{
	while(1)
	{
		DisplayAll();
		//show i on display
		ssd1306_UpdateScreen();
	}
}*/
void DisplayAll()
{
	DisplayAtlete(INCOMMING_RUNNER);
	DisplayAtlete(OUTGOING_RUNNER);
}
void DisplayAtlete(Type_Runner type)
{
	//GetAtletes:
	char string[50];
	if(type == INCOMMING_RUNNER)
	{
		strcpy(string, atlete_incoming_name);
		strcat(string, ": ");
		char timeString[10];
		if(DisplayTime(timeString, 9.58) != 0)
		{
			ssd1306_SetCursor(2, 75);
			ssd1306_WriteString("Error in DisplayTime", Font_7x10 , Black);
			return;
		}
		strcat(string, timeString);
		ssd1306_SetCursor(2,0);
	}
	else
	{
		strcpy(string, atlete_outgoing_name);
		strcat(string, ": ");
		char timeString[10];
		if(DisplayTime(timeString, 10.58) != 0)
		{
			ssd1306_SetCursor(2, 75);
			ssd1306_WriteString("Error in DisplayTime", Font_7x10, Black);
			return;
		}
		strcat(string, timeString);
		ssd1306_SetCursor(2, 2*10);

	}
	ssd1306_WriteString(string, Font_7x10, Black);

}

int DisplayTime(char* timeString, double time)
{
	if(timeString == NULL)
		return -1;
	if(time < 0)
		return -1;
	snprintf(timeString, sizeof(time), "%.3f", time);
	return 0;
}

