/*
 * uart_communication.c
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */


#include "uart_communication.h"

<<<<<<< HEAD
<<<<<<< HEAD
volatile bool receviedUART = false;

void UART_Task()

{
=======
=======
>>>>>>> 3b48119 (init)
volatile bool receivedUART = false;
uint32_t message_id = 0;
void UART_Task()

{

<<<<<<< HEAD
>>>>>>> 3b48119 (init)
=======
>>>>>>> 3b48119 (init)
	while(1)
	{
		if(receivedUART)
		{
			//handle UART
			receivedUART = false;
<<<<<<< HEAD
<<<<<<< HEAD
		}
	}
}
=======
=======
>>>>>>> 3b48119 (init)
			message_id++;

		}
	}
}

void UART_Send()
{

}
<<<<<<< HEAD
>>>>>>> 3b48119 (init)
=======
>>>>>>> 3b48119 (init)
