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

char* ShowRelayExchange(int8_t numIncoming, int8_t numOutgoing)
{
	return "need to be done\n";
}
/**
 * set the speed & distance array in atlete struct
 */
/*int RelaySetSpeed(Atlete *atlete)
{
	size_t len = 0;
	DataGetLen(&len);
	if(len <= 0)
		return -1;
	atlete->speed = (double*)malloc(sizeof(double)*len);
	atlete->distance = (double*)malloc(sizeof(double)*len);
	atlete->len = len;
	if(DataCalculate(atlete->speed,atlete->distance, len) < 0)
	{
		return -1;
	}
}*/


/**
 * find crosspoint, based on both speeds of in and out comming runner
 *return -1, no array init
 *return -2 no crosspoint
 */

/*
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
			break;
		}
		//update variabeles
		indexOutrunner++;
		inDistance = 0;
		indexInrunner = 0;
	}

	//return the  distance that was ran by the outgoing runner
	return tempDistance;
}
*/

/**
 * exchangeFrmae = frame where the exchange needs to be done.
 * timeAframe = time takes for each measurement and so the time is runed at speed[i]
 * speed= array of speed
 * len  = length of speed array
 */
/*double GetDistanceToPoint(size_t exchangeFrame, double timeAframe, Atlete* atlete)
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

*/
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
/*
double DataFindCallPoint(double time, double speedAtExchange, double exchangePoint)
{
	//exchanhgePoint - (s(distance) = v(speed) * t(time) )
	return (exchangePoint - (speedAtExchange * time));
}

void test_cross_point()
{
	DataReset();
	double distance [] =  {0.05, 0.10, 0.15, 0.20};
	double time [] = 	  {0.1,  0.1,  0.1,  0.1};

	double distance1 [] =  {0.20, 0.17, 0.13, 0.10};
	double time1 [] = 	  {0.1,  0.1,  0.1,  0.1};
	DataInit(distance[0], time[0]);
	for(uint8_t i  = 1; i < 4; i++)
		DataAdd(distance[i], time[i]);
	Atlete a;
	assert(RelaySetSpeed(&a) == 0);
	DataReset();

	DataInit(distance1[0], time1[0]);
	for(uint8_t i  = 1; i < 4; i++)
		DataAdd(distance1[i], time1[i]);
	Atlete b;
	assert(RelaySetSpeed(&b) == 0);
	double res = RelayFindCrossPoint(&b,&a);

}

void test_setspeed()
{
	DataReset();
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
	assert(a.distance[3] == 0.20);

}
void test_relay()
{
	test_setspeed();
	test_cross_point();
}*/
