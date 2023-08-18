/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

UART_buffer uart1_buffer;


void UART_Task()
{

	while(1)
	{
		if(uart1_buffer.received)
		{
			UART_Read();
		}
		osDelay(50);
	}
}

void HandleInput(UART_buffer *buffer)
{
	size_t len = (buffer->size < 20) ? buffer->size : 20;
	snprintf(atlete_incoming_name, len, "%s", buffer->data);
}
void UART_Read()
{
	//handle
	HandleInput(&uart1_buffer);
	//reset buffer
	memset(uart1_buffer.data, '\0', uart1_buffer.size);
	uart1_buffer.received = false;
	uart1_buffer.size = 0;
}

/*void UART_Send(char* msg, size_t len)
{
	HAL_UART_Transmit(huart1, (uint8_t*)msg, len);


}*/

