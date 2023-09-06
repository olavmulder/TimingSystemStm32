/*
 * display.c
 *  Created on: Jul 19, 2023
 *      Author: Olav
 */

#include "../Inc/display.h"

#define FONT_HIGHT 10
static DISPLAY_STATE displayState = MENU;
static int8_t tempRunner = -1;
static int8_t incomingRunner = -1;
static int8_t outgoingRunner = -1;
extern bool lazerIsRunning;

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

			//go to a option state from the menu view
			if(pin == LEFT && displayState == MENU)
				displayState = menuIndicator+1;

			//if pushed left in option2 set incoming runner
			//displaySTate = menu afterwards
			else if(pin == LEFT &&
					displayState == Option2)
			{
				HandleRunnerSelection(&incomingRunner, "incoming");
			}
			//if pushed left in option3 set outgoing runner
			//displaySTate = menu afterwards
			else if(pin == LEFT &&
				displayState == Option3)
			{
				HandleRunnerSelection(&outgoingRunner, "outgoing");
			}
			//if push left in other option, go back to menu
			else if(pin == LEFT)
				displayState =  MENU;

			//actually show the current state
			switch(displayState)
			{
				case MENU:
					DrawMenu(&menuIndicator, pin);
					break;
				case Option1:
					ShowAthletes(pin);
					break;
				case Option2:
				case Option3:
					SelectRunner(pin);
					break;
				case Option4:
					//StartIncoming
					StartRunner("incoming", &incomingRunner);
					break;
				case Option5:
					//start outgoing
					StartRunner("outgoing", &outgoingRunner);
					break;
				case Option6:
					//get exchange data
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

int8_t ShowAthletes(uint16_t pin)
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
	return athletesIndicator;
}

void SelectRunner(uint16_t pin)
{
	tempRunner = ShowAthletes(pin);
}
void ShortTimeMessage(char* msg, uint16_t time)
{
	ssd1306_Fill(Black);
	ssd1306_SetCursor(0,0);
	ssd1306_WriteString(msg, Font_7x10 , Black);
	ssd1306_UpdateScreen();
	osDelay(2000);
}

void HandleRunnerSelection(int8_t *runner, char* str)
{
	*runner = tempRunner;
	tempRunner = -1;
	char msg[50];
	snprintf(msg, 50, "%s = %s",str, GetAtleteNameByNumber(*runner));
	ShortTimeMessage(msg, 2000);
	displayState = MENU;
}

void StartRunner(char *str, int8_t *runner)
{
	char msg[50];

	if(*runner == -1)
	{
		snprintf(msg, 50, "first select %s", str);
		ShortTimeMessage("first select outgoing", 2000);
		displayState = MENU;
		return;
	}
	StartContinuesMeasurement();
	snprintf(msg, 50, "%s can start now", str);
	ShortTimeMessage(msg, 2000);
	uint8_t i = 0;
	while(lazerIsRunning && i < 5)
	{
		osDelay(1000);
		i++;
	}
	snprintf(msg, 50, "%s has stopped now", str);
	ShortTimeMessage(msg, 2000);
}
