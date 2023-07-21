/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

volatile bool receviedUART = false;

void UART_Task()

{
	while(1)
	{
		if(receivedUART)
		{
			//handle UART
			receivedUART = false;
		}
	}
}
