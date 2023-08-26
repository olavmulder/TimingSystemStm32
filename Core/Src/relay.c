/*
 * relay.c
 *
 *  Created on: Aug 19, 2023
 *      Author: olav
 */

#include "../Inc/relay.h"

Exchange exchanges[AMOUNT_EXCHANGES];
extern Atlete atletes[AMOUNT_ATLETES];

/**
 * Do all calcualtions with given input
 * @return
 */
int CalculateRelayExchange(int8_t numIncoming, int8_t numOutgoing)
{
	//TODO callpoint time, save marge exchange point
	double callpointTime = 0.8;
	double safeMarge = 1.00;
	//end-TODO
	Atlete *in = &atletes[numIncoming];
	Atlete *out= &atletes[numOutgoing];
	if(in == NULL || out == NULL)
		return -1;
	if(in->speed == NULL || out->speed == NULL)
		return -2;

	double crossPoint = RelayFindCrossPoint(in, out);
	crossPoint -= safeMarge;

	double timeIn;
	double timeOut;
	if(GetTimeToPoint(in, crossPoint, &timeIn) == -1)
		return -1;
	if(GetTimeToPoint(out, crossPoint, &timeOut) == -1)
		return -1;
	double takeoff = DataFindTakeOffPoint(crossPoint, timeIn, timeOut,
			in, out);
	double callpoint = DataFindCallPoint(callpointTime, in, crossPoint);

	return SetExchange(takeoff, crossPoint, callpoint, in->id, out->id);
}

int InitExchange()
{
	static uint8_t init = 0;
	if(!init)
	{

		for(size_t i = 0; i < AMOUNT_EXCHANGES; i++)
		{
			exchanges[i].takeoff = -1;
			exchanges[i].callpoint = -1;
			exchanges[i].exchangeDistance = -1;
			exchanges[i].idIn = -1;
			exchanges[i].idOut = -1;
		}
		init = 1;
		return 0;
	}
	return -1;

}
/**
 * find exchange betweein idIn & idOut, set the exchange pointer if found
 * return 0 on valid, the exchnage
 */
int GetExchange(int8_t idIn, int8_t idOut, Exchange *exchange)
{
	exchange = NULL;
	for(uint8_t i = 0; i < AMOUNT_EXCHANGES; i++)
	{
		//not init and also not found yet, so return -1
		if(idIn == -1)
			break;
		if(exchanges[i].idIn == idIn &&
		   exchanges[i].idOut == idOut)
		{
			exchange = &exchanges[i];
			if(exchange != NULL)
				return 0;
			else
				return -1;
		}
	}

	return -1;
}

int SetExchange(double takeoff, double crosspoint, double callpoint, int8_t idIn, int8_t idOut)
{
	static uint8_t amountExchanges = 0;

	if(amountExchanges >= AMOUNT_EXCHANGES)
		return -1;
	exchanges[amountExchanges].takeoff = takeoff;
	exchanges[amountExchanges].exchangeDistance = crosspoint;
	exchanges[amountExchanges].callpoint = callpoint;
	exchanges[amountExchanges].idIn = idIn;
	exchanges[amountExchanges].idOut = idOut;

	amountExchanges++;
	return 0;
}
/**
 * find crosspoint, based on both speeds of incoming and outgoing runner
 *return -1, no array init
 *return -2 no crosspoint
 */
double RelayFindCrossPoint(Atlete *in, Atlete *out)
{
	if(in == NULL || out == NULL)
	{
		return -1;
	}
	//take outgoing runner, and compare its speed at distance x
	//to speed at distance of incoming runner
	bool found = false;
	size_t indexOutrunner = 0;
	size_t indexInrunner = 0;
	double tempDistance = 0;
	double inDistance = 0;
	while(1)
	{
		if(indexOutrunner >= out->len)
			break;
		tempDistance += out->distance[indexOutrunner];
		do
		{
			//find index in incoming runner where the
			//total distance is equal to the outgoing runner

			inDistance += in->distance[indexInrunner];
			indexInrunner++;
		}while(tempDistance > inDistance);
		//if speed incoming < speed outgoing break
		if(in->speed[indexInrunner] < out->speed[indexOutrunner])
		{
			found = true;
			break;
		}
		//update variabeles
		indexOutrunner++;
		inDistance = 0;
		indexInrunner = 0;
	}

	//return the  distance that was ran by the outgoing runner
	if(found == true)
		return tempDistance;
	else
		return MAX_EXCHANGE_DISTANCE;
}
/**
 * return -1 on error(not finding distance in the right positon
 * return 0 on valid
 * *time will get the time
 */
int GetTimeToPoint(Atlete *atlete, double exchangeDistance,
					double* time)
{
	//TODO get time each frame
	double tempDistance = 0;
	double timeStep = (double)(1.0/100.0);
	size_t index = 0;
	*time = 0;
	while(tempDistance < exchangeDistance)
	{
		tempDistance += atlete->distance[index];
		*time += timeStep;
		index++;
		if(index >= atlete->len)
			return -1;
	}
	return 0;
}
double DataFindTakeOffPoint(double exchangePoint, double timeIn, double timeOut,
						Atlete *in, Atlete *out)
{
	/*
	 * v_in * t = v_out * t
	 * startXa = startXb +
	 * person to = in,
	 * person one = out
	 */
	if(in->speed == NULL || out->speed == NULL)
	{
		return (-1);
	}

	double avgSpeedIn = exchangePoint / timeIn;
	double avgSpeedOut = exchangePoint / timeOut;

	double relativeSpeed = avgSpeedIn - avgSpeedOut;
	double distanceAhead = (avgSpeedOut * timeIn) / relativeSpeed; // meters

	/*s = v * t*/
	return distanceAhead;
}

double DataFindCallPoint(double time, Atlete *atlete, double exchangePoint)
{
	//exchanhgePoint - (s(distance) = v(speed) * t(time) )
	//speed at exchange
	double tempDistance = 0;
	size_t index = 0;
	while(tempDistance < exchangePoint)
	{
		tempDistance += atlete->distance[index];
		index++;
		if(index >= atlete->len)
			return -1;
	}
	double speedAtExchange = atlete->speed[index];
	return (exchangePoint - (speedAtExchange * time));
}


