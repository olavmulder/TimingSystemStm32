/*
 * atlete.h
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */

#ifndef INC_ATLETE_H_
#define INC_ATLETE_H_

#include "storage.h"
#include "data.h"

#define AMOUNT_ATLETES 30


struct _atlete
{
	char name[NAME_LENGTH];
	double *speed;
	double *distance;
	size_t len;
	int8_t id;
	uint8_t init;
};
typedef struct _atlete Atlete;

extern int8_t currentIncomingRunner;
extern int8_t currentOutgoingRunner;

int AtleteInit();
uint8_t GetAmountAtletes();
void AtleteAddFromSDcard();
int AtleteAdd(char* name);
int AtleteSetData(int8_t id, double *speed, double *distance, size_t len);
void ShowAtlete(char*, size_t len);
char* GetAtleteNameByNumber(int8_t num);

void test_atlete();
#endif /* INC_ATLETE_H_ */
