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

TimerHandle_t Timer1_hdl;

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

/*************************************************************************
 * Function name :
 *   P_timer_hdl_t P_create_timer(uint16_t Timer_period, void (* P_timer_function)())
 *
 * Return :
 *   P_timer_hdl_t type variable representing the handle of the created timer
 *
 * Input :
 *
 *   Timer_period: An unsigned 16-bit integer representing the timer period in milliseconds.
 *   P_timer_function: A pointer to a function that will be executed when the timer expires.
 *   The function takes no arguments and returns no value.
 *
 * Output :
 *   Handle of the created timer.
 *
 * Description :
 * Creates a timer using the FreeRTOS xTimerCreate() function with the given Timer_period and P_timer_function parameters.
 * The timer is named "TIMER_TEST" and set to auto-reload. The function then starts the timer using the xTimerStart()
 * function and returns the handle of the created timer as a P_timer_hdl_t type variable.
 *
 * Notes :
 *   None
 **************************************************************************/

P_timer_hdl_t P_create_timer(uint16_t Timer_period, void (*P_timer_function)())
{
  Timer1_hdl = xTimerCreate("TIMER_TEST", Timer_period, pdTRUE, (void *)0, P_timer_function);
  xTimerStart(Timer1_hdl, 0);
  return Timer1_hdl;
}

/*************************************************************************
 * Function name :
 *   uint16_t P_delete_timer(P_timer_hdl_t Timer_hdl)
 *
 * Return :
 *   P_timer_hdl_t type variable representing the handle of the created timer
 *
 * Input :
 *
 *  Timer_hdl: A P_timer_hdl_t type variable representing the handle of the timer to be deleted.
 *
 * Output :
 *   Handle of the created timer.
 *
 * Description :
 *
 * Handle of the created timer.
 *
 * Notes :
 *   None
 **************************************************************************/

uint16_t P_delete_timer(P_timer_hdl_t Timer_hdl)
{
  if (xTimerStop(Timer_hdl, 0U) == pdPASS)
  {
    if (xTimerDelete(Timer_hdl, 0) == pdPASS)
    {
      return P_SUCCESS;
    }
    else
    {
      return P_ERROR;
    }
  }
  else
  {
    return P_ERROR;
  }
}