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

extern char uart1Buf[10];
extern volatile bool uart1Received;

#endif /* INC_UART_COMMUNICATION_H_ */
