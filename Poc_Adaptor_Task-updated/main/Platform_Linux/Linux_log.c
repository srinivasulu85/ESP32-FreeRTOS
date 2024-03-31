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
 *   void P_printf(const char *fmt, ...)
 *
 * Return :
 *   none
 *
 * Input :
 *    fmt :  format string
 *    ... : variable number of arguments that depend on the contents of the format string
 *
 * * Output :
 *   None
 *
 * Description :
 *   Prints formatted output to the console.
 *
 * Notes :
 *   None
 **************************************************************************/

void P_printf(const char *fmt, ...)
{
    va_list args;
    va_start(args, fmt);
    vprintf(fmt, args);
}
