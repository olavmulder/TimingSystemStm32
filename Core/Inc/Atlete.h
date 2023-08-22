/*
 * Atlete.h
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */

#ifndef SRC_ATLETE_H_
#define SRC_ATLETE_H_

#include "data.h"

typedef struct _exchange exchange;
struct _exchange
{
	double takeoff;
	double call;
	double exchange;
};

class Atlete {

public:
	Atlete();
	virtual ~Atlete();

	double* GetSpeed();
	char* GetName();
	double *GetTime();

	int SetTime(double *t, size_t len);
	int SetSpeed(double *s, size_t len);
	int SetName(char* n, size_t len);

private:
	double *speed;
	double *time;
	char   *name;
};

class Exchange
{
public:
	Exchange(Atlete* in, Atlete* out);

	void SetTakeoff(double takeoff);
	void SetCall(double call);
	void SetExchange(double exchange);
	void SetExchange(double takeoff, double call, double exchange);
	void Clear();

	exchange* GetExchange();

private:
	Atlete *incoming;
	Atlete *outgoing;
	exchange exch;
};
#endif /* SRC_ATLETE_H_ */
