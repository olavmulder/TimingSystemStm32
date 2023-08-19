/**
 * Get and calcualte time
 */

#include "../Inc/data.h"

Data *head;
Data *tail;


int DataInit(unsigned int distance, unsigned int time)
{
	if(head == NULL)
	{
		head = (Data*)malloc(sizeof(Data));
		if(head == NULL)
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}
	head->nPtr = NULL;
	head->time = time;
	head->distance = distance;
	tail = head;
	return 0;
}
void DataReset()
{
	Data *temp;
	while(head != NULL)
	{
		temp = head;
		head = head->nPtr;
		free(temp);
	}
}
int DataAdd(unsigned int distance, unsigned int time)
{
	Data *temp;
	temp = (Data*)malloc(sizeof(Data));
	if(temp == NULL)
	{
		return -1;
	}
	tail->nPtr = temp;
	temp->distance = distance;
	temp->time = time;
	temp->nPtr = NULL;
	tail = temp;
	return 0;
}

void DataGetLen(size_t *len)
{
	Data *temp = head;
	*len = 0;
	while(temp != NULL)
	{
		*len = *len + 1;
		temp = temp->nPtr;
	}
}
/**
 * len: size_t * (in), lenght of array of speed
 * speed: double * array, array with calculated speed.
 * return -1: speed in Null, -2 len en array size are not equal
 */
int DataCalculate(double*speed, double*distance, size_t lenIn)
{
	if(speed == NULL || distance == NULL)
	{
		return -1;
	}
	size_t len;
	DataGetLen(&len);
	if(len != lenIn)
	{
		return -2;
	}
	Data *temp = head;
	for(size_t i = 0; i < len; i++)
	{
		distance[i] = temp->distance;
		//v = s / t
		if(head->distance > 0 && head->time > 0)
			speed[i] = (double)((double)temp->distance / (double)temp->time);
		else
			speed[i] = 0;
		temp = temp->nPtr;
	}
	return 0;
}
void test_init()
{
	unsigned int distance = 100;
	unsigned int time = 2;
	assert(head == NULL);
	assert(DataInit(distance, time) == 0);
	assert(head != NULL);
	assert(DataInit(distance, time) == -1);

}
void test_add()
{
	unsigned int distance = 1000;
	unsigned int time = 4;
	assert(DataAdd(distance, time) == 0);
	assert(tail->distance == distance);
	assert(tail->time == time);
	distance = 20;
	time = 5;
	assert(DataAdd(distance, time) == 0);
	assert(tail->distance == distance);
	assert(tail->time == time);
}
void test_len()
{
	//because of test add len must be 3
	size_t len = 0;
	DataGetLen(&len);
	assert(len == 3);

}
void test_calculate()
{

	size_t len = 0;
	assert(DataCalculate(NULL,NULL, len) == -1);
	DataGetLen(&len);
	assert(len == 3);
	double speed[len];
	double distance[len];
	assert(DataCalculate(speed,distance, len) == 0);
	assert(speed[0] == 50);  // 100 /2 = 50
	assert(speed[1] == 250); // 1000/4 =250
	assert(speed[2] == 4);	 //	20 /5 = 4
	DataAdd(0,0);
	DataGetLen(&len);
	double speed1[len];
	double distance1[len];
	assert(DataCalculate(speed1,distance1, len) == 0);
}
void test_reset()
{
	assert(head != NULL);
	DataReset();
	assert(head == NULL);
}
void test_Data()
{
	test_init();
	test_add();
	test_len();
	test_calculate();
	test_reset();
}


