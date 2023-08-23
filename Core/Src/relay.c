/*
 * relay.c
 *
 *  Created on: Aug 19, 2023
 *      Author: olav
 */

#include "../Inc/relay.h"

/**
 * Do all calcualtions with given input
 * @return
 */

int ShowRelayExchange(char* returnMsg, int8_t numIncoming, int8_t numOutgoing)
{
	//TODO callpoint time
	double callpointTime = 0.8;
	Atlete *in = GetAtleteByNumber(numIncoming);
	Atlete *out= GetAtleteByNumber(numOutgoing);
	if(in == NULL || out == NULL)
		return -1;
	if(in->speed == NULL || out->speed == NULL)
		return -2;
	double crossPoint = RelayFindCrossPoint(in, out);
	double timeIn;
	double timeOut;
	if(GetTimeToPoint(in, crossPoint, &timeIn) == -1)
		return -1;
	if(GetTimeToPoint(out, crossPoint, &timeOut) == -1)
		return -1;
	double takeoff = DataFindTakeOffPoint(crossPoint, timeIn, timeOut,
			in, out);
	double callpoint = DataFindCallPoint(callpointTime, in, crossPoint);
	//SaveExchange(in, out, takeoff, callpoint);

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
		tempDistance += atlete->distance[i];
		*time += timeStep;
		index++;
		if(index >= atlete->len)
			return -1;
	}
	return 0;
}
double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
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

	double avgSpeedIn = exchangePoint / *timeIn;
	double avgSpeedOut = exchangePoint / *timeOut;

	double relativeSpeed = avgSpeedIn - avgSpeedOut;
	double distanceAhead = (avgSpeedOut * *timeIn) / relativeSpeed; // meters

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
