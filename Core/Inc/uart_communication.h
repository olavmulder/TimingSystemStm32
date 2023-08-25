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
#include "relay.h"
#include "lazer.h"
#include <string.h>

#define USART_BUFFER_SIZE	100


enum _menuOption
{
	MakeNewAtlete, ShowAllAtletes, SelectIncoming,
	SelectOutgoing, StartIncoming, StartOutgoing,
	CalculateExchangeData, GetExchangeData
};
typedef enum _menuOption MenuOptions;

enum _menuState
{
	GetAnswere, GetAnswere1, GetAnswere2,  GetMenuOption,
};
typedef enum _menuState MenuState;

void UARTTask(void *paramter);
int HandleBuffer();
int MenuAction(char* msg);
int HandleMenuOption(char* msg);
int HandleMenuAnswere(char *msg);

int ShowUI();


#endif /* INC_UART_COMMUNICATION_H_ */
