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

#include "data.h"

typedef struct _atlete Atlete;
struct _atlete
{
	char name[50];
	double *speed;
	double *distance;
	size_t len;
};

double GetDistanceToPoint(size_t exchangeFrame, double timeAframe, Atlete* atlete);
int RelaySetSpeed(Atlete *atlete);
double RelayFindCrossPoint(Atlete *in, Atlete *out);

void test_relay();
#endif /* INC_RELAY_H_ */
