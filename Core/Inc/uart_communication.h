/*
 * uart_communication.h
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

#include "cmsis_os.h"
#include "stm32f1xx_it.h"
#include "display.h"
#include <string.h>

typedef struct _UART_buffer
{
	volatile bool received;
	char data[1000];
	size_t size;
}UART_buffer;

extern UART_HandleTypeDef huart1;

void UART_Task();
void UART_Read();


extern void HandleInput(UART_buffer*);
#endif /* INC_UART_COMMUNICATION_H_ */
