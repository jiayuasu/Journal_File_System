/*
 * allocate.c
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
int allocate(int dataid,char *value)
{
	FILE *fp;

	fp=fopen("jy_files/cell_storage.txt", "w");

	printf("Allocate dataid %d value %s\n",dataid,value);
	fprintf(fp,"%d %s\n",dataid,value);
	fclose(fp);
	return 1;
}
