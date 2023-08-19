/*
 * tfmini.c
 * interfacing with TF mini
 * https://raw.githubusercontent.com/Arduinolibrary/DFRobot_TF_Mini_Laser_Range_Finder/master/SJ-GU-TFmini-T-01%20A02%20Datasheet_EN.pdf
 *  Created on: Aug 18, 2023
 *      Author: olav
 */


#include "../Inc/tfmini.h"

const size_t timeout = 100;
/*
void DataHandling_Task()
{
	const TFSetting setting = {
			.measureType = true,
			.period = 10,
			.mode = true,
			.rangeLimit = 12
	};
	unsigned long time_ms = 10;

	while(1)
	{
		bool measurementDone = false;

		if(DataInit(0,0) != 0)
		{
			exit(-1);
		}
		TFInit(setting);

		//TODO: something to start measurement
		char* recvMsg;
		size_t len;
		do{
			//get data from uart connection
			unsigned int distance = TFGetData(recvMsg, len);
			DataAdd(distance, time_ms);
		}while(measurementDone == false);

		//get speed data
		size_t lenSpeed;
		DataGetLen(&lenSpeed);
		double speed[lenSpeed];
		if(DataCalculate(speed, lenSpeed) != 0)
		{
			//TODO error
		}
		//TODO calculate exchange

	}
}
*/
void StartConfig()
{
	const char message[8] = {0x42, 0x57, 0x02, 0x00, 0x00, 0x00, 0x01, 0x02};
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}

void StopConfig()
{
	const char message[8] = {0x42, 0x57, 0x02, 0x00, 0x00, 0x00, 0x00, 0x02};
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}

/**
 * set type, mm = false,or true = cm
 */
void SetUnit(bool type)
{
	char message[8] = {0x42, 0x57, 0x02, 0x00, 0x00, 0x00, 0x00, 0x1A};
	if(type)
		message[6] = 0x01;
	//uart communication
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}

void SetOutputPeriod(unsigned int outputPeriod)
{
	char high = (outputPeriod & 0xff00) >> 8;
	char low  = (outputPeriod & 0x00ff);
	char message[8] = {0x42, 0x57, 0x02, 0x00, high, low, 0x00, 0x07};
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}
/**
 * type; true =long(0-12), false = short(0-5)
 */
void SetDistanceMode(bool type)
{
	char message[8] = {0x42, 0x57, 0x02, 0x00, 0x00, 0x00, 0x02, 0x11};
	if(type)
		message[6] = 0x07;
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}

/**
 * length m, -1 for no change
 */
void SetRangeLimit(int length)
{
	char message[8] = {0x42, 0x57, 0x02, 0x00, 0x00, 0x00, 0x00, 0x19};
	if(length > -1)
	{
		length *= 1000; // m to mm
		char high = ((length & 0xff00) > 8);
		char low  = (length & 0x00ff);
		message[4] = high;
		message[5] = low;
		message[6] = 0x01; //endable
	}
	HAL_UART_Transmit(&huart1, (uint8_t *) message, strlen(message), timeout);
}

void TFInit(TFSetting setting)
{
	StartConfig();
	SetUnit(setting.measureType);
	SetOutputPeriod(setting.period);
	SetDistanceMode(setting.mode);
	SetRangeLimit(setting.rangeLimit);
	StopConfig();
}

unsigned int TFGetData(char* msg, size_t len)
{
	if(len != 9)return -1;
	if(msg[0] != 0x59 && msg[1] != 0x59) return -1;
	char dataLow = msg[2];
	char dataHigh = msg[3];
	unsigned int distance = ((dataLow | (dataHigh << 8)) & 0xffff) ;
	return distance;
}


void test_getData()
{
	//distance = 169 cm, 0xA9;
	char msg[] = {0x59, 0x59, 0xA9, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
	assert(TFGetData(msg, sizeof(msg)) == 169);

	char msg1[] = {0x59, 0x59, 0x0A, 0XF1, 0x00, 0x00, 0x00, 0x00};
	assert(TFGetData(msg1, sizeof(msg1)) == -1);

	char msg2[] = {0x50, 0x50, 0x0A, 0XF1, 0x00, 0x00, 0x00, 0x00};
	assert(TFGetData(msg2, sizeof(msg2)) == -1);
}
void test_tf()
{
	test_getData();
}

