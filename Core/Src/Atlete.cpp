/*
 * Atlete.cpp
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */

#include "Atlete.h"

Atlete::Atlete() {
	// TODO Auto-generated constructor stub

}

Atlete::~Atlete() {
	// TODO Auto-generated destructor stub
}

double* Atlete::GetSpeed()
{
	return speed;
}
double* Atlete::GetTime()
{
	return time;
}
char* Atlete::GetName()
{
	return name;
}
int Atlete::SetSpeed(double *s, size_t len)
{
	if(s == NULL || len == 0)
		return -1;

	if(speed == NULL)
	{
		speed = (double*)malloc(sizeof(double) * len);
		if(speed == NULL)
			return -1;
		for(size_t i = 0; i < len; i++)
		{
			speed[i] = s[i];
		}
	}

}


int Atlete::SetTime(double *t, size_t len)
{
	if(t == NULL || len == 0)
		return -1;

	if(time == NULL)
	{
		time = (double*)malloc(sizeof(double) * len);
		if(time == NULL)
			return -1;
		for(size_t i = 0; i < len; i++)
		{
			time[i] = t[i];
		}
	}
}
int Atlete::SetName(char *n, size_t len)
{
	if(n == NULL || len == 0)
	{
		return -1;
	}
	name = (char*)malloc(sizeof(len));
	if(name == NULL)
		return -1;
	snprintf(name, len, "%s", n);
	return 0;
}

Exchange::Exchange(Atlete* in, Atlete *out)
{
	incoming = (Atlete*)malloc(sizeof(Atlete));
	outgoing = (Atlete*)malloc(sizeof(Atlete));
	if(incoming == NULL || outgoing == NULL)
	{
		return;
	}
	incoming = in;
	outgoing = out;

	exch.call = -1;
	exch.exchange = -1;
	exch.takeoff = -1;
}

void Exchange::SetExchange(double takeoff, double call, double exchange)
{
	exch.takeoff = takeoff;
	exch.call = call;
	exch.exchange = exchange;
}
void Exchange::SetExchange(double exchange)	{exch.exchange = exchange;}

void Exchange::SetCall(double call)			{exch.call = call;}

void Exchange::SetTakeoff(double takeoff)	{exch.takeoff = takeoff;}

void Exchange::Clear()
{
	exch.call = -1;
	exch.exchange = -1;
	exch.takeoff = -1;
}

exchange* Exchange::GetExchange()
{
	if(exch.call == -1 ||
	   exch.exchange == -1 ||
	   exch.takeoff == -1)
	{
		return NULL;
	}
	return &exch;
}

