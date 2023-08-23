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
#include "atlete.h"

typedef struct _exchange Exchange;
struct _exchange
{
	double takeoff;
	double callpoint;
	double exchangeDistance;
	int8_t idIn;
	int8_t idOut;
	Exchange *nPtr;
};


int CalculateRelayExchange(int8_t numIncoming, int8_t numOutgoing);
int GetTimeToPoint(Atlete *atlete, double exchangeDistance,
					double* time);
double RelayFindCrossPoint(Atlete *in, Atlete *out);

double DataFindTakeOffPoint(double exchangePoint, double timeIn, double timeOut,
						Atlete *in, Atlete *out);
double DataFindCallPoint(double time, Atlete* atlete, double exchangePoint);

int SaveExchange(Exchange *ex);
Exchange* GetExchange(int8_t in, int8_t out);

void test_relay();
#endif /* INC_RELAY_H_ */
