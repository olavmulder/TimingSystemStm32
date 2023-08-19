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
/*
int CalculateRelay(){
	Atlete atleteIn = {
			.name = "empty",
			.speed = NULL,
			.len = 0
	};
	Atlete atleteOut= {
			.name = "empty",
			.speed = NULL,
			.len = 0
	};
	static uint8_t number = 0; //amount times this function is called
	if(number == 0)
	{
		if(RelaySetSpeed(&atleteIn) < 0)
		{
			return -1;
		}
		//RelaySetSpeedForDistance();
		//free(atleteIn->speed);

	}
	else if(number == 1)
	{
		if(RelaySetSpeed(&atleteOut) < 0)
			return -1;

		//are both really set
		if(atleteIn.speed == NULL || atleteOut.speed == NULL)
			return -1;

		//both set, now calculate crosspoint
		int cross = RelayFindCrossPoint(&atleteIn, &atleteOut);
		if(cross < 0)
		{
			return -1;
		}
		double timeAframe = 1.0/1000.0;//temp
		double crossDistance;
		//if cross index is lager than the
		if(cross < atleteIn.len)
		{
			//returned cross ponit is from incoming atlete
			//cross point determined, so find time to reach that point for each runner
			crossDistance = GetDistanceToPoint(cross, timeAframe, atleteIn);
		}
		else
		{
			//returned crosspoint is from outgoing atlete
			crossDistance = GetDistanceToPoint(cross, timeAframe, atleteOut);
		}
	}

	number ++;
	if(number == 2) number = 0;

	return 0;
}
*/

int RelaySetSpeed(Atlete *atlete)
{
	size_t len = 0;
	DataGetLen(&len);
	if(len <= 0)
		return -1;
	atlete->speed = (double*)malloc(sizeof(double)*len);
	atlete->distance = (double*)malloc(sizeof(double)*len);
	if(DataCalculate(atlete->speed,atlete->distance, len) < 0)
	{
		return -1;
	}
}

/**
 * calcualte avg speed over DISTNACE_BETWEEN_MEASUREMENT
 */
int RelaySetSpeedForDistance(Atlete *atlete, double timeAframe)
{
	if(atlete == NULL)
		return -1;
	size_t index = 0;
	double totalDistance = 0;
	double totalTime = 0;
	for(size_t i = 0; i < atlete->len; i++)
	{
		totalTime +=timeAframe;
		totalDistance += atlete->distance[i];
		if(totalDistance >= DISTANCE_BETWEEN_MEASUREMENT)
		{
			//v = s/t
			atlete->speedDistance[index] = totalDistance / totalTime;
			totalDistance = 0;
			totalTime = 0;
			index++;
		}
	}
	return 0;

}

/**
 * find crosspoint, based on both speeds of in and out comming runner
 *return -1, no array init
 *return -2 no crosspoint
 */
int RelayFindCrossPoint(Atlete *in, Atlete *out)
{
	if(in == NULL || out == NULL)
	{
		return -1;
	}
	size_t index = 0;
	size_t min = (in->len < out->len) ? in->len : out->len;
	size_t i = 0;
	for(; i < min; i++)
	{
		if(out->speed[i] >= in->speed[i])
		{
			return i;
		}
	}
	//in case the outgoing runner has more timeframes, because it it slower
	//compare the last time of incoming runner with the outgoing runner
	for(size_t j = i; j < out->len; j++)
	{
		if(out->speed[j] >= in->speed[i])
		{
			return j;
		}
	}
	return -2;
}

/**
 * exchangeFrmae = frame where the exchange needs to be done.
 * timeAframe = time takes for each measurement and so the time is runed at speed[i]
 * speed= array of speed
 * len  = length of speed array
 */
double GetDistanceToPoint(size_t exchangeFrame, double timeAframe, Atlete* atlete)
{
	double totalTime = 0;
	double totalDistance = 0;
	for(size_t i = 0; i < exchangeFrame; i++)
	{
		//s = v*t
		totalDistance += atlete->speed[i] * timeAframe;
	}
	return totalDistance;
}


double DataFindTakeOffPoint(double exchangePoint, double* timeIn, double* timeOut,
						double* speedIn, double* speedOut, size_t len)
{
	/*
	 * v_in * t = v_out * t
	 * startXa = startXb +
	 * person to = in,
	 * person one = out
	 */
	double reactionTime = 0.200;
	if(speedIn == NULL || speedOut == NULL)
	{
		return (-1);
	}
	/*double timeForOut = GetTimeToPoint(exchangePoint, timeOut, speedOut, len, reactionTime);
	double timeForIn = GetTimeToPoint(exchangePoint, timeIn, speedIn, len, 0.00);
	double avgSpeedIn = exchangePoint / timeForIn;
	double avgSpeedOut = exchangePoint / timeForOut;

	double relativeSpeed = avgSpeedIn - avgSpeedOut;
	double distanceAhead = (avgSpeedOut * timeForIn) / relativeSpeed; // meters
	*/
	/*s = v * t*/
	//return distanceAhead;
}

double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint)
{
	//exchanhgePoint - (s(distance) = v(speed) * t(time) )
	return (exchangePoint - (speedAtExchange * time));
}


void test_setspeed()
{
	double distance [] =  {0.05, 0.10, 0.15, 0.20};
	double time [] = 	  {0.1,  0.1,  0.1,  0.1};
	DataInit(distance[0], time[0]);
	for(uint8_t i  = 1; i < 4; i++)
		DataAdd(distance[i], time[i]);
	Atlete a;
	assert(RelaySetSpeed(&a) == 0);
	assert(a.speed[0] == 0.5);
	assert(a.speed[3] == 2);
	assert(a.distance[0] == 0.05);
	assert(a.distance[4] == 0.20);
}
void test_relay()
{
	test_setspeed();

}
