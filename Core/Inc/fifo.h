/*
 * fifo.h
 *
 *  Created on: Aug 25, 2023
 *      Author: olav
 */

#ifndef INC_FIFO_H_
#define INC_FIFO_H_

#include <stdint.h>
#include <stdlib.h>
#include <stdint.h>

#define FIFO_SIZE 128

typedef struct _fifo FIFO;
struct _fifo{
	char buffer[FIFO_SIZE];
	volatile size_t head;
	volatile size_t tail;
	size_t len;
};




void FIFOInit(FIFO *fifo);
void FIFOAddData(char d, FIFO *fifo);
size_t FIFOHandleData(char* data, FIFO *fifo, size_t bytesToRead);
#endif /* INC_FIFO_H_ */
