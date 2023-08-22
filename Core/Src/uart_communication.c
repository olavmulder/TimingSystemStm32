/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

typedef enum _menuState MenuState;
enum _menuState
{
	GetAnswere, GetMenuOption
};

extern size_t uart1Bufferindex;
extern uint8_t uart1Buffer[USART_BUFFER_SIZE];
extern volatile bool uart1ReadBuffer;
extern UART_HandleTypeDef huart1;

static MenuState menuState = GetMenuOption;
static uint8_t menuoption = 0;

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
			HandleMenuAnswere(msg);
			break;
		case GetMenuOption:
			HandleMenuOption(msg);
			break;
		default:
			return -1;
			break;
	};
	return 0;
}

int HandleMenuAnswere(char *msg)
{
	switch(menuoption)
	{
	case 1:
		//incoming name

		break;
	case 2:
		//outgoing name
		break;
	case 3:
		//show result
	}
}
int HandleMenuOption(char* msg)
{
	if(strcmp(msg, "1\r") == 0)
	{
		//incoming runner
		char *str = "type name incoming runner";
		HAL_UART_Transmit(&huart1, (uint8_t *)str , strlen(str), 1000);
		menuState = GetAnswere;
		menuoption = 1;
	}
	else if(strcmp(msg, "2\r") == 0)
	{
		//outgoing runner
		menuState = GetAnswere;
		menuoption = 2;
	}
	else if(strcmp(msg, "3\r") == 0)
	{
		//show result
		menuState = GetAnswere;
		menuoption = 3;
	}
	else
	{
		char ret[] = "Not a valid option, try again\n\r";
		if(HAL_UART_Transmit(&huart1, (uint8_t *)ret , strlen(ret), 1000) != HAL_OK)
		{
			return -1;
		}
	}
	if(ShowUI() < 0)
		return -1;
	return 0;
}
int ShowUI()
{
	//menu
	const char one[] = "1: Start incoming runner\n\r";
	const char two[] = "2: Start outgoing runner\n\r";
	const char three[] = "3: show result\n\r";
	//make buffer
	char* msg;
	size_t len = sizeof(one)+ sizeof(two)+sizeof(three)+1;
	msg = (char*)malloc(len);
	if(msg == NULL)
		return -1;
	snprintf(msg, len, "%s%s%s", one, two, three);
	if(HAL_UART_Transmit(&huart1, (uint8_t *) msg, strlen(msg), 1000) != HAL_OK)
	{
		free(msg);
		return -1;
	}
	free(msg);
	return 0;
}

