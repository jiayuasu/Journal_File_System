/*
 * write.c
 *
 *  Created on: Nov 13, 2015
 *      Author: sparkadmin
 */
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <stdbool.h>
#include "phase1.h"



int WRITE_NEW_VALUE(char *value)
{
//	printf("I am creating pthread\n");
	Log log;
	Lock lock;
	int counter=0;
	int dataid=rand()%1000;
	log.state=STATE_PENDING;
	log.dataid=dataid;
	log.value=malloc(sizeof(char)*50);
	lock.dataid=dataid;
	while(Check_Lock(dataid)!=LOCK_NONE)
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
	lock.status=LOCK_EXCLUSIVE;
	Put_Lock(lock);
	strcpy(log.value,value);
	Write_Log(&log);
//	printf("I am done with creating pthread\n");

	return dataid;
}

void COMMIT(int dataid)
{
//	printf("I am doing COMMIT\n");
	//Recovery(dataid);

	Log log;
	if(dataid==-1)
	{
		/*
		 * Waiting for releasing the lock has taken more than 9 seconds. I quit.
		 */
		return;
	}
	log.dataid=dataid;
	//printf("Commit dataid is %d\n",dataid);

	printf("Let me hold the lock for 6 seconds...\n");
	sleep(6);

	log.value=malloc(sizeof(char)*50);
	Read_Log(&log);

//	printf(" got string %s\n",value);
//	strcpy(log.value,value);
	allocate(dataid,log.value);
	log.state=STATE_COMMIT;
	log.dataid=dataid;
	Write_Log(&log);
	Release_Lock(dataid);
//	printf("I am done with COMMIT\n");
//	return 1;
}
void ABORT(int dataid)
{
	//char *value=Read_Log(dataid);
	Log log;
//	log.state=STATE_ABORT;
	log.dataid=dataid;
	log.value=malloc(sizeof(char)*50);
	Read_Log(&log);
	log.state=STATE_ABORT;
	//	printf(" got string %s",value);
	//strcpy(log.value,value);
	Write_Log(&log);
	Release_Lock(dataid);
}
