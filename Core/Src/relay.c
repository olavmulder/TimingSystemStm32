/*
 * relay.c
 *
 *  Created on: Aug 19, 2023
 *      Author: olav
 */

#include "../Inc/relay.h"

static Exchange *headExchange = NULL;
static Exchange *tailExchange = NULL;

/**
 * Do all calcualtions with given input
 * @return
 */
/*int CalculateRelayExchange(int8_t numIncoming, int8_t numOutgoing)
{
	//TODO callpoint time, save marge exchange point
	double callpointTime = 0.8;
	double safeMarge = 1.00;
	//end-TODO
	Atlete *in = GetAtleteByNumber(numIncoming);
	Atlete *out= GetAtleteByNumber(numOutgoing);
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
	Exchange ex;
	ex.takeoff = takeoff;
	ex.callpoint = callpoint;
	ex.exchangeDistance = crossPoint;
	ex.idIn = in->id;
	ex.idOut = out->id;
	return SaveExchange(&ex);
}*/
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


int SaveExchange(Exchange *ex)
{
	if(headExchange == NULL)
	{
		headExchange = (Exchange*)malloc(sizeof(Exchange));
		if(headExchange == NULL)
			return -1;
		tailExchange = headExchange;
		tailExchange->callpoint = ex->callpoint;
		tailExchange->exchangeDistance = ex->exchangeDistance;
		tailExchange->takeoff = ex->takeoff;
		tailExchange->idIn = ex->idIn;
		tailExchange->idOut = ex->idOut;
		tailExchange->nPtr = NULL;
	}
	else
	{
		Exchange *temp = (Exchange*)malloc(sizeof(Exchange));
		if(temp == NULL)
			return -1;
		temp->callpoint = ex->callpoint;
		temp->exchangeDistance = ex->exchangeDistance;
		temp->takeoff = ex->takeoff;
		temp->idOut = ex->idOut;
		temp->idIn = ex->idIn;
		temp->nPtr = NULL;
		tailExchange->nPtr = temp;
		tailExchange = temp;
	}
	return 0;
}

Exchange* GetExchange(int8_t idIn, int8_t idOut)
{
	Exchange *temp = headExchange;
	while(temp != NULL)
	{
		if(temp->idIn == idIn && temp->idOut == idOut)
			return temp;
		temp = temp->nPtr;
	}
	return NULL;
}

void test_getExchange()
{
	assert(GetExchange(0,0) == NULL);
	assert(GetExchange(5,6) == headExchange);
	assert(GetExchange(7,8) == headExchange->nPtr);
}
void test_save()
{
	Exchange ex;
	ex.callpoint = 1.00;
	ex.exchangeDistance = 2.00;
	ex.takeoff = 3.00;
	ex.idIn = 5;
	ex.idOut = 6;
	assert(SaveExchange(&ex) == 0);
	ex.idIn = 7;
	ex.idOut = 8;
	assert(SaveExchange(&ex) == 0);
	assert(headExchange->idIn = 5);
	assert(tailExchange->idOut == 8);
}
void test_relay()
{
	test_save();
	test_getExchange();
}
