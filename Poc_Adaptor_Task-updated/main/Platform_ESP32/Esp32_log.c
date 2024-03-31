#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "freertos/timers.h"
#include "esp_log.h"
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