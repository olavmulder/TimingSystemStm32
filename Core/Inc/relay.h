/*
 * relay.h
 *
 *  Created on: Aug 19, 2023
 *      Author: olav
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#define MAX_EXCHANGE_DISTANCE 25
#define DISTANCE_EXCHANGE_ZONE 30
#define DISTANCE_BETWEEN_MEASUREMENT 0.10
#define AMOUNT_SPEED_DISTANCE (int)(DISTANCE_EXCHANGE_ZONE / DISTANCE_BETWEEN_MEASUREMENT)
#include "data.h"

typedef struct _atlete Atlete;

struct _atlete
{
	char name[50];
	double *speed;
	double speedDistance[AMOUNT_SPEED_DISTANCE];
	size_t len;
};

#endif /* INC_RELAY_H_ */
