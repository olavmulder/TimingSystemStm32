/*
 * storage.h
 *
 *  Created on: Sep 4, 2023
 *      Author: olav
 */

#ifndef INC_STORAGE_H_
#define INC_STORAGE_H_

#include <stdint.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

#define NAME_LENGTH 20

enum _readMode
{
	Read, Write
};
typedef enum _readMode ReadMode;


void GetStatics();
void MountStorage();
void UnmountStorage();
int8_t GetDataFromFile(char*fileName, char *buf, size_t len);
void WriteDataToFile(char* name, char* msg, size_t len);
size_t ReadTillChar(char* bufIn, char*bufOut,char c, char c2, size_t len);

#endif /* INC_STORAGE_H_ */
