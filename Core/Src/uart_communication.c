/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"
#define MESSAGE_LENGTH 9
typedef struct UARTBuffer
{
	char *buf[MESSAGE_LENGTH];
	size_t len;
};
UARTBuffer uart1Buffer;
AddBuffer(char buf)
{
	static tempIndex = 0;
	if(uart1Buffer)
	uart1Buffer->buf = (char*)realloc(uart1Buffer->buf,
							sizeof(buf)+(sizeof(char)*MESSAGE_LENGTH));

}
HandleUART()
{

	while(1)
	{
		if(uart1Received == true)
		{

			uart1Received = false;
		}
	}

}
