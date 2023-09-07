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


size_t ReadTillChar(char* bufIn, char*bufOut, char c, char c2, size_t len)
{
	size_t i = 0;
	while(*(bufIn+i) != c && *(bufIn+i) != c2 && i < len-1)
	{
		*(bufOut+i) = *(bufIn+i);
		i++;

	}
	return i+1;//reject c || c2 position
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
void UnmountStorage()
{
	f_mount(NULL, "", 0);
}

int8_t GetDataFromFile(char*fileName, char *buf, size_t len)
{
	//MountStorage();
	fres = f_open(&fil, fileName, FA_READ);
	if (fres != FR_OK)
		while(1);
	//We can either use f_read OR f_gets to get data out of files
	//f_gets is a wrapper on f_read that does some string formatting for us
	unsigned int actualRead;
	FRESULT rres = f_read(&fil,buf, len, &actualRead);
	//Be a tidy kiwi - don't forget to close your file!
	f_close(&fil);
	return rres;
}

/*
 * 1. mount storage
 * 2. write the data to the given file
 * 3. unmount storage
 */
void WriteDataToFile(char* name, char* msg, size_t len)
{
	fres = f_open(&fil, name, FA_WRITE | FA_OPEN_ALWAYS | FA_CREATE_ALWAYS);
	if(fres != FR_OK) {
		//TODO error handling
		while(1);
	}
	char tempBuf[len];
	snprintf(tempBuf, len, "%s", msg);
	unsigned int bytesWrote;
	fres = f_write(&fil, tempBuf, len, &bytesWrote);
	if(fres != FR_OK)
	{
		//TODO error handling
		while(1);
	}
	f_close(&fil);
}
