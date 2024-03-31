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

timer_t timerid;

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

/*************************************************************************
 * Function name :
 *   P_timer_hdl_t P_create_timer(uint16_t Timer_period, void (* P_timer_function)())
 *
 * Return :
 *   none
 *
 * Input :
 *   Timer_period: This is an unsigned 16-bit integer that specifies the duration of the timer in units of time.
 *   P_timer_function: This is a pointer to a function that will be executed when the timer expires
 *
 * Output :
 *   None
 *
 * Description :
 *    creates a timer using the timer_create function, sets the timer to expire in 5 seconds using timer_settime,
 *    and waits for the timer to expire using the signal functionck.
 *
 * Notes :
 *   None
 **************************************************************************/

P_timer_hdl_t P_create_timer(uint16_t Timer_period, void (*P_timer_function)())
{
	struct sigevent sev;
	struct itimerspec its;

	// Create a timer
	sev.sigev_notify = SIGEV_SIGNAL;
	sev.sigev_signo = SIGALRM;
	sev.sigev_value.sival_ptr = &timerid;
	timer_create(CLOCK_REALTIME, &sev, &timerid);

	// Set the timer to expire in 5 seconds
	its.it_value.tv_sec = 5;
	its.it_value.tv_nsec = 0;
	its.it_interval.tv_sec = 0;
	its.it_interval.tv_nsec = 0;
	timer_settime(timerid, 0, &its, NULL);

	// Wait for the timer to expire
	signal(SIGALRM, P_timer_function);
}

/*************************************************************************
 * Function name :
 *   P_delete_timer(P_timer_hdl_t)
 *
 * Return :
 *   none
 *
 * Input :
 *
 *   P_timer_hdl_t: This is a timer handle
 *
 * Output :
 *   None
 *
 * Description :
 *
 *    Delete the timer identified by the timerid variable.
 *
 * Notes :
 *   None
 **************************************************************************/

uint16_t P_delete_timer(P_timer_hdl_t)
{
	// Delete the timer
	timer_delete(timerid);
}
