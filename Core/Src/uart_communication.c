/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

extern size_t uart1Bufferindex;
extern uint8_t uart1Buffer[USART_BUFFER_SIZE];
extern volatile bool uart1ReadBuffer;
extern UART_HandleTypeDef huart1;
void HandleBuffer()
{
	//tf mini zooi;
	//copy data
	size_t len = strlen(uart1Buffer);
	char dataToUse[len];
	memcpy(dataToUse, uart1Buffer, len);
	MenuAction(msg);
	//rest buffer
	memset(uart1Buffer, '\0', sizeof(uart1Buffer));
	uart1Bufferindex = 0;
	uart1ReadBuffer = false;
}
int MenuAction(char* msg)
{
	if(strcmp(msg, "1") == 0)
	{
		//incoming runner
	}
	else if(strcmp(msg, "2") == 0)
	{
		//outgoing runner
	}
	else if(strcmp(msg, "3") == 0)
	{
		//show result
	}
	else
	{
		char ret[] = "Not a valid option";
		HAL_UART_Transmit(&huart1, (uint8_t *)ret , strlen(ret), 1000);
	}
	if(ShowUI() < 0)
		return -1;
}
int ShowUI()
{
	//menu
	const char one[] = "1: Start incoming runner\n";
	const char two[] = "2: Start outgoing runner\n";
	const char three[] = "3: show result\n";
	//make buffer
	char* msg;
	size_t len = sizeof(one)+ sizeof(two)+sizeof(three)+1;
	msg = (char*)malloc(len);
	if(msg == NULL)
		return -1;
	snprintf(msg, len, "%s%s%s", one, two, three);
	HAL_UART_Transmit(&huart1, (uint8_t *) msg, strlen(msg), 1000);
	free(msg);
	return 0;
}

