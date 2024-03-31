#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <errno.h>
#include <signal.h>
#include <time.h>
#include <stdarg.h>
#include "../Platform_Adaptor/Platform_Adaptor.h"

/************************************************************************
 *  Defines section
 *************************************************************************/

/************************************************************************
 * TYPEDEFS
 *************************************************************************/

/************************************************************************
 * Function Prototype Section
 *************************************************************************/
static void main_task_function();

/************************************************************************
 * EXPORTED VARIABLES
 *************************************************************************/

/************************************************************************
 * LOCAL VARIABLES
 *************************************************************************/
pthread_t main_task_id;

void main(void)
{
	pthread_create(&main_task_id, NULL, (void *)main_task_function, NULL);
	wait_task(&main_task_id);
	//while (1);
}

static void main_task_function()
{
	static int temp = 1;
	if (temp == 1)
	{
		Platform_Adaptor_main();
		temp = 0;
	}
}
