/*
 * data.h
 *
 *  Created on: Aug 18, 2023
 *      Author: olav
 */

#ifndef INC_DATA_H_
#define INC_DATA_H_

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <assert.h>

typedef struct _data Data;
struct _data
{
	double distance; //distance in centimeters
	double time;//time in milliseconds
	Data 		 *nPtr;
};


int DataInit(double distance, double time);
void DataReset();
int DataAdd(double distance, double time);
void DataGetLen(size_t *len);
int DataCalculate(double*speed, double*distance, size_t lenIn);

void test_Data();
#endif /* INC_DATA_H_ */
