/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"


#define STRING_LENGTH 30
char menuOptionString[8][STRING_LENGTH] =
{
		"\r --Menu-- \r",
		"1: Make new atlete\r",
		"2: Show all atletes\r",
		"3: Select incoming runner\r",
		"4: Select outgoing runner\r",
		"5: Start incoming runner\r",
		"6: Start outgoing runner\r",
		"7: Show exchange data\r"

};
char menuResponse[3][STRING_LENGTH] =
{
		"type name: ",
		"type incoming number: ",
		"type outgoing number: ",

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
		  HandleBuffer();
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
	MenuAction(dataToUse);

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
			break;
	};
	return 0;
}

int HandleMenuAnswere(char *msg)
{

	int res = 0;
	char *name = NULL;
	int8_t num = -1;
	char retmsg[50];

	switch(menuoption)
	{
	case MakeNewAtlete:

		if(AtleteGetHead() == NULL)
			res =  InitAtlete(msg);
		else
			res =  AtleteAdd(msg);

		break;
	case SelectIncoming:
		num = (int8_t)atoi(msg);

		if((name = GetAtleteNameByNumber(num)) == NULL)
		{
			//send error
			HAL_UART_Transmit(&huart1, (uint8_t *)"NOT A VALID NUMBER\r",
								strlen("NOT A VALID NUMBER\r"), 1000);
			res = -1;
			break;
		}
		if(num != currentOutgoingRunner)
		{
			currentIncomingRunner = num;
			snprintf(retmsg, 50, "%d:%s selected as incoming", num, name);
			HAL_UART_Transmit(&huart1, (uint8_t *)retmsg, strlen(retmsg), 1000);
		}
		else{
			snprintf(retmsg, 50, "number is same as incoming runner, try again\r");
			HAL_UART_Transmit(&huart1, (uint8_t *)retmsg, strlen(retmsg), 1000);
		}
		break;
	case SelectOutgoing:
		num = (int8_t)atoi(msg);
		if((name = GetAtleteNameByNumber(num)) == NULL)
		{
			//send error
			HAL_UART_Transmit(&huart1, (uint8_t *)"NOT A VALID NUMBER\r",
								strlen("NOT A VALID NUMBER\r"), 1000);
			break;
		}

		if(num != currentIncomingRunner)
		{
			currentOutgoingRunner = num;
			snprintf(retmsg, 50, "%d:%s selected as outgoing", num, name);
			HAL_UART_Transmit(&huart1, (uint8_t *)retmsg, strlen(retmsg), 1000);
		}
		else{
			snprintf(retmsg, 50, "number is same as outgoing runner, try again\r");
			HAL_UART_Transmit(&huart1, (uint8_t *)retmsg, strlen(retmsg), 1000);
		}
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
		char* str = ShowAtlete();
		if(str != NULL)
		{
			HAL_UART_Transmit(&huart1, (uint8_t *)str, strlen(str), 1000);
			free(str);
		}else
			HAL_UART_Transmit(&huart1, (uint8_t *)"empty...", strlen("empty..."), 1000);
		ShowUI();
		menuState = GetMenuOption;
	}
	else if(strcmp(msg, "3\r") == 0)
	{
		//select incoming runner
		HAL_UART_Transmit(&huart1, (uint8_t *)menuResponse[1] , strlen(menuResponse[1]), 1000);
		menuState = GetAnswere;
		menuoption = SelectIncoming;
	}
	else if(strcmp(msg, "4\r") == 0)
	{
		//select outgoing runner
		HAL_UART_Transmit(&huart1, (uint8_t *)menuResponse[2] , strlen(menuResponse[2]), 1000);
		menuState = GetAnswere;
		menuoption = SelectOutgoing;
	}
	else if(strcmp(msg, "5\r") == 0)
	{
		//start incoming runner....
		char retmsg[100];
		char *name = GetAtleteNameByNumber(currentIncomingRunner);
		snprintf(retmsg, 100, "start incoming with: %s\r", name);

		ShowUI();
		menuState = GetMenuOption;

	}
	else if(strcmp(msg, "6\r") == 0)
	{
		//start outgoing runner.....
		char retmsg[100];
		char *name = GetAtleteNameByNumber(currentOutgoingRunner);
		snprintf(retmsg, 100, "start outgoing with: %s\r", name);
		ShowUI();
		menuState = GetMenuOption;
	}
	else if(strcmp(msg, "7\r") == 0)
	{
		//show exchange data
		char* retmsg = ShowRelayExchange(currentIncomingRunner, currentOutgoingRunner);
		if(HAL_UART_Transmit(&huart1, (uint8_t *)retmsg , strlen(retmsg), 1000) != HAL_OK)
		{
			return -1;
		}
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

