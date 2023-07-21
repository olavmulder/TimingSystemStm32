/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

<<<<<<< HEAD
volatile bool receviedUART = false;

void UART_Task()

{
=======
volatile bool receivedUART = false;
uint32_t message_id = 0;
void UART_Task()

{

>>>>>>> 3b48119 (init)
	while(1)
	{
		if(receivedUART)
		{
			//handle UART
			receivedUART = false;
<<<<<<< HEAD
		}
	}
}
=======
			message_id++;

		}
	}
}

void UART_Send()
{

}
>>>>>>> 3b48119 (init)
