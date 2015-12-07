/*
 * deallocate.c
 *
 *  Created on: Nov 13, 2015
 *      Author: sparkadmin
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include "phase1.h"
int deallocate()
{
	FILE *fp;
	int offset=0;
	int diskDataid;
	int blankDataid=-1;
	char blankValue=' ';
	char *diskTuple=malloc(sizeof(int)+sizeof(char));
	char *blankDiskTuple=malloc(sizeof(int)+sizeof(char));
	memcpy(blankDiskTuple,&blankDataid,sizeof(int));
	memcpy(blankDiskTuple+sizeof(int),&blankValue,sizeof(char));
	fp=fopen("jy_cellstorage.txt", "w");
	fclose(fp);
	return 0;
}

