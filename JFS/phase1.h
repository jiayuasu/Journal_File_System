/*
 * phase1.h
 *
 *  Created on: Nov 13, 2015
 *      Author: sparkadmin
 */


#ifndef PHASE1_H_
#define PHASE1_H_

#define LOCK_NONE 0
#define LOCK_EXCLUSIVE 1
#define LOCK_SHARE 2

#define LogSize (sizeof(int)*2+sizeof(char))
#define LockSize (sizeof(int)*2)
#define ActionSize (sizeof(int)*2)
#define DataSize (sizeof(int)*2+sizeof(char))

#define STATE_PENDING 0
#define STATE_COMMIT 1
#define STATE_ABORT 2

#define SleepTime 1
typedef struct Log
{
	int state;
	int dataid;
	char* value;
}Log;
typedef struct Lock
{
	int dataid;
	int status;
}Lock;
typedef struct Action
{
    int actionid;
    int state;
}Action;
typedef struct Data
{
    int dataid;
    char value;
    int actionid;
}Data;

 int Check_Lock(int dataid);
 int Put_Lock(Lock lock);
 int Release_Lock(int dataid);
 int Write_Log(Log *log);
 void Read_Log(Log *log);
 int Recovery(int dataid);
 int allocate(int dataid,char* value);
 int deallocate();
 int WRITE_NEW_VALUE(char* value);
 void COMMIT(int dataid);
 void ABORT(int dataid);
 char* READ_CURRENT_VALUE(int dataid);
#endif /* PHASE1_H_ */
