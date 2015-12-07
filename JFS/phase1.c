/*
 * phase1.c
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
#include <sys/signal.h>
int main()
{
	printf("Test Case 1-----------------\n");
	TestCase1();
	printf("Test Case 2-----------------\n");
	TestCase2();
	printf("Test Case 3-----------------\n");
	TestCase3();
	printf("Test Case 4-----------------\n");
	TestCase4();
	printf("Test Case 5-----------------\n");
	TestCase5();
	printf("Test Case 6-----------------\n");
	TestCase6();
	printf("Test Case 7-----------------\n");
	TestCase7();
}


void TestCase1()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid;
	char *input1="testcase1";
	char *input2="NotATestCase";
	char *readReturn1;
	char *readReturn2;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,input1);
	pthread_join(t1,&dataid);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid);
	pthread_join(t2,NULL);

/*
 * Start test case
 */

	pthread_create(&t3,NULL,(void *)&READ_CURRENT_VALUE,dataid);
	pthread_join(t3,(void**)&readReturn1);

	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,input2);
	pthread_join(t1,&dataid);

	pthread_create(&t4,NULL,(void *)&ABORT,dataid);
	pthread_join(t4,NULL);

	pthread_create(&t3,NULL,(void *)&READ_CURRENT_VALUE,dataid);
	pthread_join(t3,(void**)&readReturn2);


	if(strcmp(readReturn1,readReturn2)==0)
	{
		printf("Test Case 1 Pass\n");
	}
	else
	{
		printf("Test Case 1 Fail\n");
	}

}


void TestCase2()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid;
	char *readReturn1;
	char *readReturn2;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"NotATestCase");
	pthread_join(t1,&dataid);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid);
	pthread_join(t2,NULL);

/*
 * Start test case
 */

	pthread_create(&t3,NULL,(void *)&READ_CURRENT_VALUE,dataid);
	pthread_join(t3,(void**)&readReturn1);

	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"testcase2");
	pthread_join(t1,&dataid);
	pthread_create(&t4,NULL,(void *)&COMMIT,dataid);
	pthread_join(t4,NULL);

	pthread_create(&t3,NULL,(void *)&READ_CURRENT_VALUE,dataid);
	pthread_join(t3,(void**)&readReturn2);


	if(strcmp(readReturn2,"testcase2")==0)
	{
		printf("Test Case 2 Pass\n");
	}
	else
	{
		printf("Test Case 2 Fail\n");
	}
}


void TestCase3()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid1,dataid2;
	char *readReturn1;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"testcase3");
	pthread_join(t1,&dataid1);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid1);
	pthread_join(t2,NULL);
/*
 * Start test case
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"NotATestCase");
	pthread_join(t1,&dataid2);
	pthread_create(&t4,NULL,(void *)&COMMIT,dataid2);
	pthread_join(t4,NULL);

	pthread_create(&t3,NULL,(void *)&READ_CURRENT_VALUE,dataid2);
	pthread_join(t3,(void**)&readReturn1);




	if(strcmp(readReturn1,"NotATestCase")==0)
	{
		printf("Test Case 3 Pass\n");
	}
	else
	{
		printf("Test Case 3 Fail\n");
	}
}


void TestCase4()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid1,dataid2;
	char *readReturn;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"testcase4");
	pthread_join(t1,&dataid1);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid1);
/*
 * Start test case
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"BreakTheTest");
	pthread_join(t1,&dataid2);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid2);
	pthread_join(t2,NULL);
	/*
	 * Read the current value
	 */
		pthread_create(&t5,NULL,(void *)&READ_CURRENT_VALUE,dataid1);
		pthread_join(t5,(void**)&readReturn);
		if(strcmp(readReturn,"BreakTheTest")==0)
		{
			printf("Test Case 4 Pass\n");
		}
		else printf("Test Case 4 Fail\n");

}

void TestCase5()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid1,dataid2;
	char *readReturn;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"testcase5");
	pthread_join(t1,&dataid1);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid1);
	pthread_join(t2,NULL);
/*
 * Start test case
 */
	pthread_create(&t3,NULL,(void *)&WRITE_NEW_VALUE,"BreakTheTest");
	pthread_join(t3,&dataid2);
	pthread_create(&t4,NULL,(void *)&COMMIT,dataid2);
	/*
	 * Kill the commit thread
	 */
	printf("Kill the second thread\n");
	pthread_cancel(t4);
/*
 * Read the current value
 */
	pthread_create(&t5,NULL,(void *)&READ_CURRENT_VALUE,dataid1);
	pthread_join(t5,(void**)&readReturn);
	if(strcmp(readReturn,"testcase5")==0)
	{
		printf("Test Case 5 Pass\n");
	}
	else if(strcmp(readReturn,"ERROR")==0)
	{
		printf("No previouse committed value. Test Case 5 Pass\n");
	}
}

void TestCase6()
{
	pthread_t t1,t2,t3,t4,t5;
	int result;
	int dataid1,dataid2;
	char *readReturn;
/*
 * Pre write something to the disk for further testing
 */
	pthread_create(&t1,NULL,(void *)&WRITE_NEW_VALUE,"testcase6");
	pthread_join(t1,&dataid1);
	pthread_create(&t2,NULL,(void *)&COMMIT,dataid1);

/*
 * Start test case
 */
	pthread_create(&t3,NULL,(void *)&WRITE_NEW_VALUE,"BreakTheTest");


	/*
	 * Kill the commit thread
	 */
	printf("Kill the first thread\n");
	pthread_cancel(t2);
	pthread_join(t3,&dataid2);
	pthread_create(&t4,NULL,(void *)&COMMIT,dataid2);
	pthread_join(t4,NULL);
	/*
	 * Read the current value
	 */
		pthread_create(&t5,NULL,(void *)&READ_CURRENT_VALUE,dataid1);
		pthread_join(t5,(void**)&readReturn);
		if(strcmp(readReturn,"testcase5")==0)
		{
			printf("Test Case 6 Pass\n");
		}
		else printf("Test Case 6 Fail\n");

}

void TestCase7()
{
	pthread_t t[10],tRead;
	pthread_t c[10];
	int result,i;
	int dataid[10];
	char *readReturn;
	for(i=0;i<10;i++)
	{
		if(i==9)
		{
			pthread_create(&t[i],NULL,(void *)&WRITE_NEW_VALUE,"dataid9");
		}
		else
		{
			pthread_create(&t[i],NULL,(void *)&WRITE_NEW_VALUE,"abcde");
		}
		pthread_join(t[i],&dataid[i]);
		pthread_create(&c[i],NULL,(void *)&COMMIT,dataid[i]);
	}
	pthread_create(&tRead,NULL,(void *)&READ_CURRENT_VALUE,dataid[0]);
	pthread_join(tRead,(void**)&readReturn);
	if(strcmp(readReturn,"dataid9")==0)
	{
		printf("Test Case 7 Pass\n");
	}
	else printf("Test Case 7 Fail\n");

}
