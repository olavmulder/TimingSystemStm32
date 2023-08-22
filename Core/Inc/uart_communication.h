/*
 * uart_communication.h
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */

#ifndef INC_UART_COMMUNICATION_H_
#define INC_UART_COMMUNICATION_H_

#include "stm32f1xx_it.h"
#include "cmsis_os.h"

#include "display.h"
#include <string.h>

#define USART_BUFFER_SIZE	100

void UARTTask();
void HandleBuffer();
int MenuAction(char* msg);
int ShowUI();


#endif /* INC_UART_COMMUNICATION_H_ */
