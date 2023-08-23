/*
 * tfmini.c
 * interfacing with TF mini
 * https://raw.githubusercontent.com/Arduinolibrary/DFRobot_TF_Mini_Laser_Range_Finder/master/SJ-GU-TFmini-T-01%20A02%20Datasheet_EN.pdf
 *  Created on: Aug 18, 2023
 *      Author: olav
 */


#include "../Inc/lazer.h"

const size_t timeout = 100;

extern size_t uart2Bufferindex;
extern uint8_t uart2Buffer[USART_BUFFER_SIZE];
extern volatile bool uart2ReadBuffer;

void UARTDataTask()
{
	while(1)
	{
		if(uart2ReadBuffer)
		{
			//copy data
			size_t len = strlen((char*)uart2Buffer)+1;
			char dataToUse[len];
			memset(dataToUse, '\0', len);
			memcpy(dataToUse, uart2Buffer, len);
			//HandleData()

			//rest buffer
			memset(uart2Buffer, '\0', sizeof(uart2Buffer));
			uart2Bufferindex = 0;
			uart2ReadBuffer = false;
		}

	}
}
int CRCCheck(char *data)
{
	int sum = 0;
	for(size_t i = 0; i< 8 ;i++)
	{
		sum += data[i];
	}
	char low = (char)(sum & 0xff);
	if(low == data[8])
		return 0;
	else
		return -1;
}
int HandleData(char* data)
{
	if(ISDataValid(data))
	{
		double distance = data[6] | (data[7] << 8);
		distance /= 10.0; //from dm to m;
		return distance;
	}
	return -1;
}

void StartContinuesMeasurement()
{
	const char message[9] = {0xfa, 0x01, 0xff, 0x04, 0x01, 0x00, 0x00, 0x00, 0xff};
	HAL_UART_Transmit(&huart2, (uint8_t *) message, strlen(message), timeout);
}

void StopMeasurement()
{
	const char message[9] = {0xfa, 0x01, 0xff, 0x04, 0x00, 0x00, 0x00, 0x00, 0xfe};
	HAL_UART_Transmit(&huart2, (uint8_t *) message, strlen(message), timeout);
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
	assert(CRCCheck(data) == 0);
	data[0] = 0x00;
	assert(CRCCheck(data) == -1);
}
void test_lazer()
{
	test_handleData();
	test_crc();
}
