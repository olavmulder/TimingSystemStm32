/*
 * tfmini.h
 *
 *  Created on: Aug 18, 2023
 *      Author: olav
 */

#ifndef INC_TFMINI_H_
#define INC_TFMINI_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <stdbool.h>
#include "data.h"

typedef struct _tfSetting TFSetting;
struct _tfSetting{
	bool measureType;// false = mm, true = cm
	unsigned int period; //hz 100 is default
	bool mode; //false = short, true = long
	int rangeLimit; // -1 disabled;
};
extern UART_HandleTypeDef huart1;

void TFInit(TFSetting setting);
unsigned int TFGetData(char *msg, size_t len);
void test_tf();
#endif /* INC_TFMINI_H_ */
