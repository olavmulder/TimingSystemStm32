#include "../Inc/fifo.h"



void FIFOInit(FIFO *fifo)
{
	fifo->head = 0;
	fifo->tail = 0;
	fifo->len = 0;
	memset(fifo->buffer, 0, FIFO_SIZE);
}

void FIFOAddData(char d, FIFO *fifo)
{
	fifo->buffer[fifo->head] = d;
	fifo->head++;
	fifo->len ++;
	if((fifo->head == fifo->tail) && fifo->len > 0)
	{
		// overflow error
	}

	//out of bound
	if(fifo->head >= FIFO_SIZE)
		fifo->head = 0;

}

size_t FIFOHandleData(char* data, FIFO *fifo, size_t bytesToRead)
{
	if(fifo->len < bytesToRead)
		bytesToRead = fifo->len;

	for(size_t i = 0; i < bytesToRead; i++)
	{
	  data[i] = fifo->tail;
	  fifo->tail++;
	  if(fifo->tail >= FIFO_SIZE)
	  {
		  fifo->tail = 0;
	  }
	}
	fifo->len -= bytesToRead;
	return bytesToRead;
}


