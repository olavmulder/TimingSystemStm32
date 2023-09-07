/*
 * atlete.c
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */
#include "../Inc/atlete.h"

Atlete atletes[AMOUNT_ATLETES];
uint8_t amountAtletes = 0;


uint8_t GetAmountAtletes()
{
	return amountAtletes;
}
/**
 * init the array, only call it once
 * return 0 on valid, return -1 if already init
 */
int AtleteInit()
{
	static uint8_t init = 0;
	if(init == 1)
		return -1;

	for(uint8_t i = 0; i < AMOUNT_ATLETES;i++)
	{
		memset(atletes[i].name, '\0', NAME_LENGTH);
		atletes[i].distance = NULL;
		atletes[i].speed = NULL;
		atletes[i].len = 0;
		atletes[i].id = 0;
		atletes[i].init = 0;
	}
	init = 1;
	return 0;
}
void AtleteAddFromSDcard()
{


	//make buffer to read from
	const uint16_t len = AMOUNT_ATLETES*NAME_LENGTH+2;
	char buffer[len];
	memset(buffer, '\0', len);
	//set all data in buffer
	if(GetDataFromFile("names.txt", buffer, len) != 0)
		while(1);
	uint16_t i = 0;
	size_t add = 0;
	//read till buffer
	if(buffer[0] != '[')
	{
		//TODO error on screen!!
		while(1);
	}
	i = 1; //elliminate the '[' char

	do
	{
		char tempBuf[NAME_LENGTH];
		memset(tempBuf, '\0', NAME_LENGTH);
		i += ReadTillChar(buffer+i, tempBuf, ',', ']', NAME_LENGTH);
		if(AtleteAdd(tempBuf) != 0)
		{
			//TODO error on screen!!
			while(1);
		}
	}while(buffer[i-1] != ']');
}
/**
 * add name to array
 * return -1 if array is full
 */
int AtleteAdd(char* name)
{
	if(amountAtletes > AMOUNT_ATLETES)
		return -1;
	snprintf(atletes[amountAtletes].name, NAME_LENGTH, "%s", name);

	atletes[amountAtletes].id = amountAtletes;
	atletes[amountAtletes].speed = NULL;
	atletes[amountAtletes].distance = NULL;
	atletes[amountAtletes].len = 0;
	atletes[amountAtletes].init = 1;
	amountAtletes++;
	return 0;
}
/**
 *set data in array for 'id'
 *if id is not init, return -1 and return -1 on malloc errors
 *return 0 on valid
 */
int AtleteSetData(int8_t id, double *speed, double *distance, size_t len)
{
	//not init, don't set
	if(atletes[id].init == 0)
		return -1;

	if(atletes[id].distance == NULL)
		atletes[id].distance = (double*)malloc(sizeof(double)*len);
	else
		return -1;

	if(atletes[id].speed == NULL)
		atletes[id].speed = (double*)malloc(sizeof(double)*len);
	else
		return -1;

	if(atletes[id].distance == NULL || atletes[id].speed == NULL)
		return -1;

	atletes[id].len = len;
	for(size_t i = 0; i < len; i++)
	{
		atletes[id].distance[i] = distance[i];
		atletes[id].speed[i] = speed[i];
	}
	return 0;
}

void ShowAtlete(char* str, size_t len)
{
	//reset string
	memset(str, '\0', len);
	for(uint8_t i = 0; i < amountAtletes; i++)
	{
		char tempStr[NAME_LENGTH+6];
		memset(tempStr, '\0', NAME_LENGTH+6);
		snprintf(tempStr, sizeof(tempStr), "%d:%s\n", atletes[i].id, atletes[i].name);
		strcat(str, tempStr);
	}
}
char* GetAtleteNameByNumber(int8_t num)
{
	if(atletes[num].init == false)
		return NULL;
	return atletes[num].name;
}

void test_atlete_init()
{
	assert(AtleteInit() == 0);
	assert(atletes[1].init == 0);
	assert(atletes[AMOUNT_ATLETES-1].distance == NULL);
	assert(AtleteInit() == -1);
}
void test_show_all()
{
	size_t len = AMOUNT_ATLETES * (NAME_LENGTH+6);
	char str[len];
	ShowAtlete(str, len);
}

void test_addatlete()
{
	assert(AtleteAdd("Olav") == 0);
	assert(amountAtletes == 1);
	assert(AtleteAdd("Sven") == 0);
	assert(amountAtletes == 2);
	double s[] = {3.00, 4.00};
	assert(AtleteSetData(0, s,s,2) == 0);
	assert(AtleteSetData(1, s,s,2) == 0);
	assert(AtleteSetData(2, s,s,2) == -1);

	assert(atletes[0].distance[0] == 3.00);
	assert(atletes[0].speed[1] == 4.00);

	assert(atletes[1].distance[0] == 3.00);
	assert(atletes[1].speed[1] == 4.00);
}
void test_atlete()
{
	test_atlete_init();
	test_addatlete();
	test_show_all();
}
