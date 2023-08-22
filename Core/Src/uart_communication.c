/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

#define STRING_LENGTH 25
char menuOptionString[3][STRING_LENGTH] =
{
		"\r Menu \r",
		"1: Make new atlete\r",
		"2: Show all atletes\r"
};
char menuResponse[1][20] =
{
		"type name: "

};

extern size_t uart1Bufferindex;
extern uint8_t uart1Buffer[USART_BUFFER_SIZE];
extern volatile bool uart1ReadBuffer;
extern UART_HandleTypeDef huart1;

static MenuState menuState = GetMenuOption;
static MenuOptions menuoption = MakeNewAtlete;

void UARTTask()
{
	while(1)
	{
		if(uart1ReadBuffer)
		{
		  if(HandleBuffer() < 0)
		  {
			  exit(-1);
		  }
		}
		osDelay(20);
	}
}
int HandleBuffer()
{
	//copy data
	size_t len = strlen((char*)uart1Buffer)+1;
	char dataToUse[len];
	memset(dataToUse, '\0', len);
	memcpy(dataToUse, uart1Buffer, len);
	if(MenuAction(dataToUse) < 0)
	{
		return -1;
	}
	//rest buffer
	memset(uart1Buffer, '\0', sizeof(uart1Buffer));
	uart1Bufferindex = 0;
	uart1ReadBuffer = false;
	return 0;
}

int MenuAction(char* msg)
{
	switch(menuState)
	{
		case GetAnswere:
			return HandleMenuAnswere(msg);
			break;
		case GetMenuOption:
			return HandleMenuOption(msg);
			break;
		default:
			return -1;
			break;
	};
	return 0;
}

int HandleMenuAnswere(char *msg)
{

	int res;
	switch(menuoption)
	{
	case MakeNewAtlete:

		if(AtleteGetHead() == NULL)
			res =  InitAtlete(msg);
		else
			res =  AtleteAdd(msg);

		break;
	default:
		return -1;
	}
	menuState = GetMenuOption;
	ShowUI();

	return res;
}
int HandleMenuOption(char* msg)
{
	if(strcmp(msg, "1\r") == 0)
	{
		//Make new atlete
		HAL_UART_Transmit(&huart1, (uint8_t *)menuResponse[0] , strlen(menuResponse[0]), 1000);
		menuState = GetAnswere;
		menuoption = MakeNewAtlete;
	}
	else if(strcmp(msg, "2\r") == 0)
	{
		if(AtleteGetHead() == NULL)
			return -1;
		char* str = ShowAtlete();
		if(str == NULL)
			return -1;
		HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 1000);
		free(str);
		ShowUI();
		menuState = GetMenuOption;
	}
	else

	{
		char ret[] = "Not a valid option, try again\n\r";
		if(HAL_UART_Transmit(&huart1, (uint8_t *)ret , strlen(ret), 1000) != HAL_OK)
		{
			return -1;
		}
	}
	return 0;
}
int ShowUI()
{
	for(size_t i = 0; i < sizeof(menuOptionString) / STRING_LENGTH;i++)
	{
		if(HAL_UART_Transmit(&huart1, (uint8_t *) menuOptionString[i], strlen(menuOptionString[i]), 1000) != HAL_OK)
		{
			return -1;
		}
	}
	return 0;
}

