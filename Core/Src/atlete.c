/*
 * atlete.c
 *
 *  Created on: Aug 22, 2023
 *      Author: olav
 */
#include "../Inc/atlete.h"
Atlete *headAtlete = NULL;
Atlete *tailAtlete = NULL;
static uint8_t atleteId = 0;

Atlete *AtleteGetHead(){return headAtlete;}

int InitAtlete(char* name)
{

	if(headAtlete != NULL || name == NULL)
		return -1;

	headAtlete = (Atlete*)malloc(sizeof(Atlete));
	if(headAtlete == NULL)
		return -1;

	tailAtlete = headAtlete;
	//init fields
	tailAtlete->nPtr = NULL;
	tailAtlete->speed = NULL;
	tailAtlete->distance = NULL;
	tailAtlete->id  = atleteId;
	tailAtlete->len = 0;
	snprintf(tailAtlete->name, NAME_LENGTH, "%s", name);
	return 0;
}

/**
 * return id
 */
int AtleteAdd(char* name)
{
	Atlete *temp = (Atlete*)malloc(sizeof(Atlete));
	if(temp == NULL)
		return -1;

	//update linked list
	tailAtlete->nPtr = temp;
	tailAtlete = temp;

	//set field values
	snprintf(tailAtlete->name, NAME_LENGTH, "%s", name);
	tailAtlete->id = ++atleteId;
	tailAtlete->nPtr = NULL;
	tailAtlete->speed = NULL;
	tailAtlete->distance = NULL;
	tailAtlete->len = 0;

	return atleteId;
}
/**
 * Set the speed and distance array including the length of the array
 * in the atlete struct, based on the given id.
 */
int AtleteSetData(int8_t id, double *speed, double *distance, size_t len)
{
	Atlete *temp = headAtlete;
	if(temp == NULL)
		return -1;

	while(temp != NULL)
	{
		if(temp->id == id)
		{
			if(temp->distance == NULL)
				temp->distance = (double*)malloc(sizeof(double)*len);
			else
				return -1;
			if(temp->speed == NULL)
				temp->speed = (double*)malloc(sizeof(double)*len);
			else
				return -1;

			if(temp->distance == NULL || temp->speed == NULL)
				return -1;

			temp->len = len;
			for(size_t i = 0; i < len; i++)
			{
				temp->distance[i] = distance[i];
				temp->speed[i] = speed[i];
			}
			return 0;
		}
		temp = temp->nPtr;
	}
	return -1;
}
char* ShowAtlete()
{
	const size_t len = NAME_LENGTH+6;
	size_t totalLenght = len;
	char *str = (char*)malloc(len);
	memset(str, '\0', len);

	Atlete *temp = headAtlete;
	if(temp == NULL)
		return NULL;
	while(temp != NULL)
	{
		char tempStr[len];
		memset(tempStr, '\0', len);
		snprintf(tempStr, sizeof(tempStr), "%d:%s\n", temp->id, temp->name);
		strcat(str, tempStr);
		totalLenght += len;
		str = (char*)realloc(str, totalLenght);
		temp = temp->nPtr;
	}
	return str;
}
char* GetAtleteNameByNumber(int8_t num)
{
	Atlete *temp = headAtlete;
	while(temp != NULL)
	{
		if(temp->id == num)
		{
			return temp->name;
		}
		temp = temp->nPtr;
	}
	return NULL;
}
Atlete* GetAtleteByNumber(int8_t num)
{
	Atlete *temp = headAtlete;
	while(temp != NULL)
	{
		if(temp->id == num)
			return temp;
		temp = temp->nPtr;
	}
	return NULL;
}
void test_show_all()
{
	char* res = ShowAtlete();
	assert(strlen(res) == strlen("0:Olav\n1:Sven\n"));
	assert(strcmp("0:Olav\n1:Sven\n", res) == 0);
}
void test_initAtlete()
{
	assert(InitAtlete(NULL) == -1);
	char *name = "Olav";
	assert(InitAtlete(name) == 0);
	assert(InitAtlete(name) == -1);
	assert(headAtlete == tailAtlete);
}

void test_ateletesetdata()
{
	double s[] = {1.00, 2.00};
	double d[] = {1.00, 2.00};
	assert(AtleteSetData(0, s, d, 2) == 0);
	assert(headAtlete->distance[0] == 1.00);
	assert(headAtlete->speed[1] == 2.00);
	assert(AtleteSetData(1, s,d,2) == -1);
}
void test_addatlete()
{
	assert(AtleteAdd("Sven") == atleteId);
	assert(atleteId == 1);
	double s[] = {3.00, 4.00};
	assert(AtleteSetData(1, s,s,2) == 0);
	assert(tailAtlete->distance[0] == 3.00);
	assert(tailAtlete->speed[1] == 4.00);
}
void test_atlete()
{
	test_initAtlete();
	test_ateletesetdata();
	test_addatlete();
	test_show_all();
}
