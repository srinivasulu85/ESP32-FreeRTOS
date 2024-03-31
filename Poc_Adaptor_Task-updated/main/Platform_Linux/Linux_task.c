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

/************************************************************************
 * EXPORTED VARIABLES
 *************************************************************************/

/************************************************************************
 * LOCAL VARIABLES
 *************************************************************************/

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

/*************************************************************************
 * Function name :
 *   uint16_t P_create_task(P_task_id_t *task_id,
		uint32_t task_priority,
		void (* task_function)())
 *
 * Return :
 *   none
 *
 * Input :
 *
 *  task_id:       A pointer to a P_task_id_t type variable used to store the task ID of the created task.
 *  task_priority: A 32-bit unsigned integer value representing the priority of the task.
 *  task_function: A function pointer to the task function that needs to be executed. The function should have no parameters and no return value.
 *
 * Output :
 *   None
 *
 * Description :
 *
 *   Creates a new task with the specified task function and priority.
 *
 * Notes :
 *   None
 **************************************************************************/

uint16_t P_create_task(P_task_id_t *task_id,
					   uint32_t task_priority,
					   void (*task_function)()) /* Function pointer*/
{

	pthread_create(task_id, NULL, (void *)task_function, NULL);
}

/*************************************************************************
 * Function name :
 *
 * void wait_task(pthread_t *temp)
 *
 *
 * Return :
 *   none
 *
 * Input :
 *
 *    ms - the number of milliseconds to sleep for.
 *
 *
 * Output :
 *
 *   waits for the specified thread to terminate.
 *
 *
 * Description :
 *
 *  waits for the specified thread to terminate by calling the pthread_join() function
 *
 * Notes :
 *   None
 **************************************************************************/

void wait_task(pthread_t *temp)
{

	pthread_join(*temp, NULL);
}

/*************************************************************************
 * Function name :
 *
 * void P_sleep_task ( uint32_t ms );
 *
 *
 * Return :
 *   none
 *
 * Input :
 *
 *    ms - the number of milliseconds to sleep for.
 *
 *
 * Output :
 *   None
 *
 * Description :
 *
 *  Puts the current task to sleep for the specified number of milliseconds.
 *
 * Notes :
 *   None
 **************************************************************************/

void P_sleep_task(uint32_t ms)
{
	struct timespec ts;

	ts.tv_sec = ms / 1000;				// seconds
	ts.tv_nsec = (ms % 1000) * 1000000; // nanoseconds

	while (nanosleep(&ts, &ts) == -1);
}

int P_delete_task(P_task_id_t *task_id)
{
  P_printf("Task Deleted ..!\n");
    pthread_exit(exit);

}
