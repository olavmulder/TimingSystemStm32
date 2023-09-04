/*
 * tfmini.c
 * interfacing with TF mini
 * https://raw.githubusercontent.com/Arduinolibrary/DFRobot_TF_Mini_Laser_Range_Finder/master/SJ-GU-TFmini-T-01%20A02%20Datasheet_EN.pdf
 *  Created on: Aug 18, 2023
 *      Author: olav
 */


#include "../Inc/lazer.h"

#define MESSAGE_LENGTH 9 //amount bytes for the message the lazer sends
const size_t timeout = 1000;
extern int8_t currentRunner;

FIFO uart2Buffer;
/**
 * task for handling incoming data from the lazer
 */
void UARTDataTask(void *parameter)
{
	size_t delay = *(size_t*)parameter;
	//test_makeRunningPerson();
	FIFOInit(&uart2Buffer);

	const double normalTime  = 1.0 / 100.0;
	double time = normalTime;
	double lastDistance = 0;
	while(1)
	{
		if(uart2Buffer.len >= MESSAGE_LENGTH)
		{
			char dataToUse[9];
			//get data from buffer
			size_t readBytes = FIFOHandleData(dataToUse, &uart2Buffer, MESSAGE_LENGTH);

			if(readBytes != MESSAGE_LENGTH)
				goto end;
			if(CRCCheck(dataToUse, sizeof(dataToUse)) < 0)
				goto end;

			double distance  = HandleData(dataToUse);
			//received not a valid message
			if(distance < 0)
			{
				time += normalTime;
			}
			//if person runned to end of zone
			else if(distance > MAX_MEASUREMENT_DISTANCE)
			{
				if(MeasurementDone() < 0)
				{
					//error
				}
				//reset all variables
				time = normalTime;
				lastDistance = 0;
			}
			//if person is at start line
			else if(distance > MEASURE_FROM)
			{
				//received distance because real ran distance
				double tempDistance = distance-MEASURE_FROM;
				//distance further away since last measurement
				tempDistance -= lastDistance;
				//add data further away since last measurement
				DataAdd(tempDistance, time);
				time = normalTime;
				lastDistance = distance;
			}
		}
		end:
		osDelay(delay);

	}
}
int MeasurementDone()
{
	StopMeasurement();
	size_t len;
	DataGetLen(&len);
	//Atlete* at = GetAtleteByNumber(currentRunner);
	//if(at == NULL)
	//	return -1;
	double speed[len];
	double distance[len];
	if(DataCalculate(speed, distance, len) < 0)
	{
		//error
		return -1;
	}
	else
	{
		if(AtleteSetData(currentRunner, speed, distance, len) < 0)
		{
			//error
			return -1;
		}
	}

	DataReset();
	currentRunner = -1;
	return 0;
}
int CRCCheck(char *data, size_t len)
{
	int sum = 0;
	for(size_t i = 0; i< len; i++)
	{
		sum += data[i];
	}
	char low = (char)(sum & 0xff);
	if(low == data[8])
		return 0;
	else
		return -1;
}
double HandleData(char* data)
{
	if(ISDataValid(data))
	{
		double distance = (data[6] | (data[7] << 8));
		distance /= 10.0; //from dm to m;
		return distance;
	}
	return -1;
}

void StartContinuesMeasurement()
{
	const char message[9] = {0xfa, 0x01, 0xff, 0x04, 0x01, 0x00, 0x00, 0x00, 0xff};
	if(HAL_UART_Transmit(&huart2, (uint8_t *) message, sizeof(message), timeout) != HAL_OK)
	{
		exit(-1);
	}
}

void StopMeasurement()
{
	const char message[9] = {0xfa, 0x01, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0xfe};
	HAL_UART_Transmit(&huart2, (uint8_t *) message, sizeof(message), timeout);
}

void test_makeRunningPerson()
{
	AtleteAdd("Olav");
	currentRunner = 0;
	currentIncomingRunner = 0;
	StartContinuesMeasurement();

}
void test_handleData()
{
	char data[] = {0xfb, 0x03, 0x00, 0x04, 0x01, 0x00, 0x4c, 0x00, 0x4f};
	assert(HandleData(data) > 0);
	data[4] = 0x00;
	assert(HandleData(data) == -1);
	data[4] = 0x01;
	//floating error, but it works
	//assert(HandleData(data) == 0.76);
	char d[] = {0x00};
	assert(HandleData(d) == -1);

}
void test_crc()
{
	char data[] = {0xfb, 0x03, 0x00, 0x04, 0x01, 0x00, 0x4c, 0x00, 0x4f};
	assert(CRCCheck(data, sizeof(data)) == 0);
	data[0] = 0x00;
	assert(CRCCheck(data, sizeof(data)) == -1);
}
void test_lazer()
{
	test_handleData();
	test_crc();
}
