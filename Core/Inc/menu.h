/*
 * uart_communication.h
 *
 *  Created on: Jul 21, 2023
 *      Author: olav
 */

#ifndef INC_MENU_H_
#define INC_MENU_H_

#include "stm32f1xx_it.h"
#include "cmsis_os.h"

#include "display.h"
#include "relay.h"
#include "lazer.h"
#include <string.h>

#define AMOUNT_OPTIONS 6
enum _Option{
	Show_Athletes, Select_Incoming, Select_Outgoing,
	Start_Incoming, Start_Outgoing,Get_Exchangedata
};
typedef enum _Option OPTION;

static inline char* enumToString(OPTION o)
{
	static const char *strings[] = {
			"Show athletes", "Select incoming", "Select outgoing",
			"Start incoming", "Start outgoing", "Get exchange"
	};
	return strings[o];
}




#endif /* INC_MENU_H_ */
