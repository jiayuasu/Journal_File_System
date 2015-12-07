/*
 * read.c
 *
 *  Created on: Nov 13, 2015
 *      Author: sparkadmin
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include <stdbool.h>
#include "phase1.h"

char* READ_CURRENT_VALUE(int arg)
{

	int dataid=arg;
	int diskDataid;
	int counter=0;
	if(Recovery(dataid)==0)
	{
		return "ERROR";
	}
	char *value=malloc(sizeof(char)*50);
	Lock lock;
	while(Check_Lock(dataid)==LOCK_EXCLUSIVE)
	{
		if(counter<3)
		{
			counter++;
			sleep(3);
		}
		else
		{
			printf("I have been waiting for 9 seconds. I quit.\n");
			return -1;
		}
	}
	lock.dataid=arg;
	lock.status=LOCK_SHARE;
	Put_Lock(lock);
	FILE *fp;
	fp=fopen("jy_files/cell_storage.txt", "r");
	fscanf(fp,"%d %s\n",&dataid,value);
	printf("I am reading dataid %d value %s\n",arg,value);
	Release_Lock(arg);
	return value;
}
