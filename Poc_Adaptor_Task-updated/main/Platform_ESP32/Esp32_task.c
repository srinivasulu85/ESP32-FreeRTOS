#include "esp_err.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_spiffs.h"

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

void app_main()
{
  init_file_system();
  Platform_Adaptor_main();
}

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

/*************************************************************************
 * Function name :
 *
 * uint16_t P_create_task(P_task_id_t *P_task_id,
 *                         uint32_t P_task_priority,
 *                         void (* P_task_function)())
 *
 *
 *
 * Return :
 *    Status of the task creation process.
 *
 * Input :
 *
 *    P_task_id: a pointer to a P_task_id_t type variable that will be used to store the task identifier returned by the function.
 *    P_task_priority: an unsigned 32-bit integer that specifies the priority of the task being created.
 *    P_task_function: a pointer to a function that will be executed by the task when it is created.
 *
 * Output :
 *
 *    It creates a new task and returns a status code indicating the success or failure of the task creation process.
 *
 * Description :
 *
 *    Creates a new task using the FreeRTOS xTaskCreate() API function
 *
 * Notes :
 *   None
 **************************************************************************/

uint16_t P_create_task(P_task_id_t *P_task_id,
                       uint32_t P_task_priority,
                       void (*P_task_function)())
{
  uint16_t r_status;
  r_status = P_ERROR;
  if (xTaskCreate(P_task_function,
                  "Task1",
                  (3092 / sizeof(portSTACK_TYPE)),
                  NULL,
                  P_task_priority,
                  P_task_id) == pdPASS)
  {
    r_status = P_SUCCESS;
  }
  return r_status;
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
  ms /= portTICK_PERIOD_MS;
  if (ms == 0u)
  {
    ms = 1u;
  }
  vTaskDelay(ms);
}

int P_delete_task(P_task_id_t *task_id)
{
  P_printf("I am inside P_delete_task\n");
  
  vTaskDelete(task_id);

  // Return status of task deletion operation
  return P_SUCCESS;
}