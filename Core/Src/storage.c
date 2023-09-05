/*
 * storage.c
 *
 *  Created on: Sep 4, 2023
 *      Author: olav
 */


#include "../Inc/storage.h"
#include "fatfs.h"
#include <stdarg.h> //for va_list var arg functions

FATFS fatFS;
FIL fil;
FRESULT fres;

size_t ReadTillChar(char* bufIn, char*bufOut, char c, size_t len)
{
	size_t i = 0;
	while(*(bufIn+i) != c && i < len-1)
	{
		*(bufOut+i) = *(bufIn+i);
		i++;

	}
	return i+1;//reject '\n'
}
void GetStatics()
{
	DWORD free_clusters, free_sectors, total_sectors;
	FATFS* getFreeFs;
	fres = f_getfree("", &free_clusters, &getFreeFs);
	if (fres != FR_OK) {
		while(1);
	}
	//Formula comes from ChaN's documentation
	total_sectors = (getFreeFs->n_fatent - 2) * getFreeFs->csize;
	free_sectors = free_clusters * getFreeFs->csize;

}
void MountStorage()
{
	fres = f_mount(&fatFS, "",1); //1=mount now
	if(fres != FR_OK)
	{
		while(1);
	}
}

void OpenFile(char* fileName, ReadMode mode)
{
	if(mode == Read)
		fres = f_open(&fil, fileName, FA_READ);
	else if(mode == Write)
		fres = f_open(&fil, fileName, FA_WRITE);
	if (fres != FR_OK)
		while(1);
}
int8_t GetData(char *buf, size_t len)
{
	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	int8_t res;
	unsigned int actualRead;
	FRESULT rres = f_read(&fil,buf, len, &actualRead);
	if(rres == 0)
		res = 0;
	else
		res = -1;
	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
	return res;
}
