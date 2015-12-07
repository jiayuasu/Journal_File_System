/*
 * utils.c
 *
 *  Created on: Nov 13, 2015
 *      Author: sparkadmin
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include "phase1.h"

int Check_Lock(int dataid)
{
//	printf("I am checking a lock\n");
	FILE *fp;
	int diskDataid;
	int diskStatus;
	int status=0;
//	char* diskLock=malloc(sizeof(int)*2);
	fp=fopen("jy_log_lock/lock.txt", "r");
	if(fp==NULL)
	{
		printf("No lock file. Let's continue.\n");
		return 0;
	}
	while(fscanf(fp,"%d %d\n",&diskDataid,&diskStatus)==2)
	{

		//if(diskDataid==dataid)
		//{
			status=diskStatus;
		//}

	}
	fclose(fp);
	if(status==0)
	{
		printf("No lock, let's continue\n");
		return LOCK_NONE;
	}
	else
	{
		printf("There is a lock, let's wait\n");
		return status;
	}
}
int Put_Lock(Lock lock)
{
	FILE *fp;
	//char *diskLock=malloc(sizeof(int)*2);
	fp=fopen("jy_log_lock/lock.txt", "a");
	//memcpy(diskLock,&(lock.dataid),sizeof(int));
	//memcpy(diskLock+sizeof(int),&(lock.status),sizeof(int));
	fprintf(fp,"%d %d\n",lock.dataid,lock.status);
	//fputs(diskLock,fp);
	fclose(fp);
//	free(diskLock);
	return 1;
}
int Release_Lock(int dataid)
{
	FILE *fp;
	fp=fopen("jy_log_lock/lock.txt", "a");
	fprintf(fp,"%d %d\n",dataid,LOCK_NONE);
	fclose(fp);
	return 1;
}
int Write_Log(Log *log)
{

	FILE *fp;

	fp=fopen("jy_log_lock/log.txt", "a");

//	printf("I wrote log data id %d state %d value %s\n",log->dataid,log->state,log->value);

	fprintf(fp,"%d %d %s\n",log->state,log->dataid,log->value);

	fclose(fp);

	//free(diskLog);
//	printf("I am done with writing a log\n");
	return 1;
}
void Read_Log(Log *log)
{
//	printf("I am reading a log\n");
	FILE *fp;


	int diskState,diskDataid;
	//char diskValue[50];
	char *diskValue=malloc(sizeof(char)*50);
	fp=fopen("jy_log_lock/log.txt", "r");
	if(fp==NULL)
	{
		printf("No log file.\n");
//		return "NoLogFile";
	}
	//printf("Read log dataid %d\n",log->dataid);
	while(fscanf(fp,"%d %d %s\n",&diskState,&diskDataid,diskValue)==3)
	{
		if(diskDataid==log->dataid)
		{
			//printf("I got log data id %d state %d value %s\n",diskDataid,diskState,diskValue);
			log->state=diskState;
			strcpy(log->value,diskValue);
		}
	}


	fclose(fp);

//	printf("I am done with reading a log\n");

//	return log;
}

void Read_Last_Log(Log *log)
{
//	printf("I am reading a log\n");
	FILE *fp;


	int diskState,diskDataid;
	//char diskValue[50];
	char *diskValue=malloc(sizeof(char)*50);
	fp=fopen("jy_log_lock/log.txt", "r");
	if(fp==NULL)
	{
		printf("No log file.\n");
//		return "NoLogFile";
	}
	//printf("Read log dataid %d\n",log->dataid);
	while(fscanf(fp,"%d %d %s\n",&diskState,&diskDataid,diskValue)==3)
	{
		//if(diskDataid==log->dataid)
		//{
			//printf("I got log data id %d state %d value %s\n",diskDataid,diskState,diskValue);
			log->state=diskState;
			strcpy(log->value,diskValue);
		//}
	}


	fclose(fp);

//	printf("I am done with reading a log\n");

//	return log;
}

void Read_Last_Commit_Log(Log *log)
{
//	printf("I am reading a log\n");
	FILE *fp;
//	log.value=malloc(sizeof(char)*50);


	int diskState,diskDataid;
	char diskValue[50];

	fp=fopen("jy_log_lock/log.txt", "r");
	if(fp==NULL)
	{
		printf("No log file.\n");
		//return "NoLogFile";
	}

	while(fscanf(fp,"%d %d %s\n",&diskState,&diskDataid,diskValue)==3)
	{
		//if(diskDataid==log->dataid)
		//{
			if(diskState==STATE_COMMIT)
			{
				log->state=diskState;
				strcpy(log->value,diskValue);
			}

		//}
	}


	fclose(fp);

//	printf("I am done with reading a log\n");

//	return log;
}

int Recovery(int dataid)
{
	Log log;
	log.dataid=dataid;
	log.state=STATE_PENDING;
	log.value=malloc(sizeof(char)*50);
	Read_Last_Log(&log);
	if(log.state==STATE_PENDING)
	{
		printf("Last write is still pending.\n");
		if(Check_Lock(dataid)==LOCK_EXCLUSIVE)
					{
						printf("Wait for last write and sleep 6 seconds.\n");
						sleep(6);
						if(Check_Lock(dataid)==LOCK_EXCLUSIVE)
						{
							printf("Last write got error1.\n");
							Release_Lock(dataid);

						}
						else
						{return 1;}
					}

		Read_Last_Commit_Log(&log);
		if(log.state!=STATE_COMMIT)
		{
			printf("No committed value\n");
			deallocate();
			return 0;
		}
		else
		{
		//printf("Allocate the last value again\n");
		//COMMIT(dataid);
		return 1;
		}
	}
	else
	{
		if(Check_Lock(dataid)==LOCK_EXCLUSIVE)
			{
				printf("Last write got error2.\n");
				Release_Lock(dataid);
				return 1;
			}
		return 1;

	}
}
