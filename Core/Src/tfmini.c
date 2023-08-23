/*
 * tfmini.c
 * interfacing with TF mini
 * https://raw.githubusercontent.com/Arduinolibrary/DFRobot_TF_Mini_Laser_Range_Finder/master/SJ-GU-TFmini-T-01%20A02%20Datasheet_EN.pdf
 *  Created on: Aug 18, 2023
 *      Author: olav
 */


#include "../Inc/tfmini.h"

const size_t timeout = 100;

void UARTDataTask()
{
	while(1)
	{

	}
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

