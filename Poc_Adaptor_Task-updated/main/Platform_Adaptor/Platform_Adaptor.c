#include <stdio.h>
#include <stdarg.h>
#include <string.h>
#include "Platform_Adaptor.h"

/************************************************************************
 *  Defines section
 *************************************************************************/

/************************************************************************
 * TYPEDEFS
 *************************************************************************/

/************************************************************************
 * Function Prototype Section
 *************************************************************************/
void Timer_test_callback(P_timer_hdl_t P_Timer);

/************************************************************************
 * EXPORTED VARIABLES
 *************************************************************************/

/************************************************************************
 * LOCAL VARIABLES
 *************************************************************************/
static P_task_id_t Adaptor_task_tid;
static uint8_t Create_timer = 1;
static P_timer_hdl_t Timer_hdl_id;

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

/*************************************************************************
 * Function name :
 *   void Platform_Adaptor_main( void )
 *
 * Return :
 *   none
 *
 * Input :
 *
 *   none
 *
 * Output :
 *   If the task is created successfully, the message "Main task created successfully" is printed to
 *   the console. If the task is not created successfully, no message is printed
 *
 * Description :
 *   Creates a new task
 *
 * Notes :
 *   None
 **************************************************************************/

void Platform_Adaptor_main(void)
{
    if (P_create_task(&Adaptor_task_tid,
                      PTASK_LOWEST_PRIORITY,
                      (void *)Adaptor_task) == P_SUCCESS)
    {
        P_printf("Main task created successfully\n");
    }
   
    P_sleep_task(10000);

    if (P_delete_task(Adaptor_task_tid) == P_SUCCESS)
    {
        P_printf("Adaptor task deleted successfully\n");
    }
}

/*************************************************************************
 * Function name :
 *   void Timer_test_callback(P_timer_hdl_t P_Timer)
 *
 * Return :
 *   none
 *
 * Input :
 *   P_Timer :  To identify the timer that expired and caused the callback function to be executed
 *
 * Output :
 *   none
 *
 * Description :
 *   Handle to the timer that triggered the callback
 *
 * Notes :
 *   None
 **************************************************************************/
void Timer_test_callback(P_timer_hdl_t P_Timer)
{
    P_printf("Timer is expired\n");

    if (P_delete_timer(P_Timer) == P_SUCCESS)
    {
        P_printf("Timer deleted successfully\n");
    }
    else
    {
        P_printf("Failed to delete timer\n");
    }
}

/*************************************************************************
 * Function name :
 *   void Adaptor_task(void)
 *
 * Return :
 *   none
 *
 * Input :
 *   none
 *
 * Output :
 *   none
 *
 * Description :
 *   Handle file I/O operations and timer creations.
 *
 * Notes :
 *   None
 **************************************************************************/

void Adaptor_task(void)
{
    P_printf("Executing Main task\n");

    P_file_t *file = P_fopen("/spiffs/test.txt", "w");
    if (file == NULL)
    {
        printf("Failed to open file for writing\n");
    }
    else
    {
        char *message = "Poc_Adaptor";
        size_t bytes_written = P_fwrite(message, sizeof(char), strlen(message), file);
        if (bytes_written != strlen(message))
        {
            printf("Failed to write to file\n");
        }
        else
        {
            printf("Data written to file successfully\n");
        }
        P_fclose(file);
    }

    file = P_fopen("/spiffs/test.txt", "r");

    if (file == NULL)
    {
        printf("Failed to open file for reading\n");
    }
    else
    {
        // read data from file using P_fgets
        char line[50];
        while (P_fgets(line, sizeof(line), file) != NULL)
        {
            P_printf("Data read using P_fgets: %s\n", line);
        }

        // read data from file using P_fread
        rewind((FILE *)file); // move file pointer to beginning of file
        char buffer[50];
        size_t bytes_read = P_fread(buffer, sizeof(char), sizeof(buffer), file);
        if (bytes_read == 0)
        {
            printf("No data read from file\n");
        }
        else
        {
            printf("Data read using P_fread: %s\n", buffer);
        }

        int result = P_fclose(file);
        if (result != 0)
        {
            printf("Failed to close file\n");
        }
    }

    for (;;)
    {
        if (Create_timer == 1)
        {
            Create_timer = 0;
            Timer_hdl_id = P_create_timer(100, Timer_test_callback);
            P_printf("Timer created successfully..!\n");
        }

        P_sleep_task(1000);
    }
}
