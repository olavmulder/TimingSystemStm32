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
void HandleBuffer()
{
	//tf mini zooi;
	//copy data
	size_t len = strlen(uart1Buffer);
	char dataToUse[len];
	memcpy(dataToUse, uart1Buffer, len);
	//rest buffer
	memset(uart1Buffer, '\0', sizeof(uart1Buffer));
	uart1Bufferindex = 0;
	uart1ReadBuffer = false;
}




