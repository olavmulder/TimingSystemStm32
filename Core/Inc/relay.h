/*
 * relay.h
 *
 *  Created on: Aug 19, 2023
 *      Author: olav
 */

#ifndef INC_RELAY_H_
#define INC_RELAY_H_

#include "data.h"
#include "atlete.h"

#define MAX_EXCHANGE_DISTANCE 25
#define DISTANCE_EXCHANGE_ZONE 30
#define AMOUNT_EXCHANGES	30


struct _exchange
{
	double takeoff;
	double callpoint;
	double exchangeDistance;
	int8_t idIn;
	int8_t idOut;
};
typedef struct _exchange Exchange;


int InitExchange();
int SetExchange(double takeoff, double crosspoint, double callpoint,
				int8_t idIn, int8_t idOut);
int GetExchange(int8_t idIn, int8_t idOut, Exchange *exchange);

int CalculateRelayExchange(int8_t numIncoming, int8_t numOutgoing);
int GetTimeToPoint(Atlete *atlete, double exchangeDistance,
					double* time);
double RelayFindCrossPoint(Atlete *in, Atlete *out);

double DataFindTakeOffPoint(double exchangePoint, double timeIn, double timeOut,
						Atlete *in, Atlete *out);
double DataFindCallPoint(double time, Atlete* atlete, double exchangePoint);



void test_relay();
#endif /* INC_RELAY_H_ */
