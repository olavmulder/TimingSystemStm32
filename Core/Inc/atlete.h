/*
 * atlete.h
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */

#ifndef INC_ATLETE_H_
#define INC_ATLETE_H_

#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>

#define NAME_LENGTH 20

typedef struct _atlete Atlete;
struct _atlete
{
	char name[20];
	double *speed;
	double *distance;
	size_t len;
	int8_t id;
	Atlete *nPtr;
};


int InitAtlete(char* name);
int AtleteAdd(char* name);
int AtleteSetData(int8_t id, double *speed, double *distance, size_t len);

void test_atlete();
#endif /* INC_ATLETE_H_ */
