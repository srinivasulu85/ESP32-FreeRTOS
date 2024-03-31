
#ifndef PLATFORM_ADAPTOR_H
#define PLATFORM_ADAPTOR_H

/**************************************************************************
 *  Include section
 ***************************************************************************/
#include <stdio.h>
#include <inttypes.h>
#include <stdint.h>
#include <pthread.h>

/*************************************************************************
 * TYPEDEFS
 **************************************************************************/
typedef uint32_t P_task_id_t;
typedef uint32_t P_timer_hdl_t;
typedef uint16_t *P_file_t;

/*************************************************************************
 * Defines Section
 **************************************************************************/

#define PTASK_HIGHEST_PRIORITY 9
#define PTASK_HIGH_PRIORITY 7
#define PTASK_NORMAL_PRIORITY 5
#define PTASK_LOW_PRIORITY 3
#define PTASK_LOWEST_PRIORITY 2

/* Platfrom error codes */
#define P_SUCCESS 0
#define P_ERROR 1

/************************************************************************
 * EXTERNAL VARIABLES
 *************************************************************************/

/************************************************************************
 * Function Declaration Section
 *************************************************************************/

void app_main(void);

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

void Platform_Adaptor_main(void);

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

void Adaptor_task(void);

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
                       void (*P_task_function)());

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

P_timer_hdl_t P_create_timer(uint16_t Timer_period, void (*P_timer_function)());

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

uint16_t P_delete_timer(P_timer_hdl_t Timer_hdl);

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

void P_sleep_task(uint32_t ms);

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

void wait_task(pthread_t *temp);

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

void P_printf(const char *fmt, ...);

/*************************************************************************
 * Function name :
 *
 *   P_file_t P_fopen(const char *file_name, const char *mode_of_operation)
 *
 * Return :
 *
 *   Success : A file handle (P_file_t)
 *   Failure  : NULL
 *
 * Input :
 *
 *   file_name: the name of the file to be opened
 *   mode_of_operation: the mode in which to operate on the file
 *
 *  Output :
 *  A file handle if the file is successfully opened.
 *  NULL if the file cannot be opened.
 *
 * Description :
 *
 *   opens a file specified by its name and mode of operation and returns a file handle.
 *   It prints an error message and returns NULL if the file cannot be opened.
 *
 * Notes :
 *   None
 **************************************************************************/

P_file_t P_fopen(const char *file_name, const char *mode_of_operation);

/*************************************************************************
 * Function name :
 *
 *   size_t P_fwrite(const void *ptr, size_t size, size_t count, P_file_t *file)
 *
 * Return :
 *
 *    Returns the number of items written to the file.
 *
 *
 * Input :
 *
 *   ptr: pointer to the array of elements to be written to the file.
 *   size: size in bytes of each element to be written.
 *   count: number of elements to be written.
 *   file: file handle pointer.
 *
 *  Output :
 *
 *  Writes the specified number of elements from the array pointed to by ptr
 *  to the file associated with the given file handle.
 *
 * Description :
 *
 *   Writes the specified number of elements from the array pointed to by ptr
 *   to the file associated with the given file handle.
 *
 * Notes :
 *   None
 **************************************************************************/

size_t P_fwrite(const void *ptr, size_t size, size_t count, P_file_t *file);

/*************************************************************************
 * Function name :
 *
 *   size_t P_fread(void *ptr, size_t size, size_t nmemb, P_file_t *file)
 *
 * Return :
 *
 *    size_t: the number of elements read successfully.
 *
 * Input :
 *
 *   ptr: pointer to the buffer where the read elements are stored.
 *   size: size in bytes of each element to be read.
 *   nmemb: number of elements to be read.
 *   file: file handle pointer.
 *
 *  Output :
 *
 *   The read data will be stored in the memory pointed to by *ptr
 *
 *
 * Description :
 *
 *   Reads a specified number of elements of a specified size from a file pointed
 *   To by the provided file handle and stores them in a buffer pointed to by ptr.
 *
 *
 * Notes :
 *   None
 **************************************************************************/

size_t P_fread(void *ptr, size_t size, size_t nmemb, P_file_t *file);

/*************************************************************************
 * Function name :
 *
 *   char P_fgets(char *str, int n, P_file_t *file)
 *
 * Return :
 *
 *    size_t: the number of elements read successfully.
 *
 * Input :
 *
 *   str: pointer to the buffer where the string read will be stored
 *   int n: maximum number of characters to be read (including the null terminator)
 *   file: pointer to the file handle
 *
 *  Output :
 *
 *   The function reads a string from a file and returns a pointer to it if successful.
 *   If the end-of-file is reached before any characters are read, it returns NULL.
 *
 *
 * Description :
 *
 *   Reads a specified number of elements of a specified size from a file pointed
 *   To by the provided file handle and stores them in a buffer pointed to by ptr.
 *
 *
 * Notes :
 *   None
 **************************************************************************/

char P_fgets(char *str, int n, P_file_t *file);

/*************************************************************************
 * Function name :
 *
 *   int P_fclose(P_file_t *file)
 *
 * Return :
 *
 *    size_t: the number of elements read successfully.
 *
 * Input :
 *
 *   file: a pointer to a file handle to be closed
 *
 *  Output :
 *
 *  Closes a file specified by its file handle. If the file handle is invalid,
 *  it prints a message indicating failure and returns the EOF constant.
 *
 *
 * Description :
 *
 *   This function closes the file specified by the file handle..
 *
 *
 * Notes :
 *   None
 **************************************************************************/

int P_fclose(P_file_t *file);

/*************************************************************************
 * Function name :
 *   void init_file_system()
 *
 * Return :
 *   none
 *
 * Input :
 *
 *   None
 *
 * Output :
 *   None
 *
 * Description :
 *   Initializes the Virtual File System (VFS) by registering
 *   the SPI Flash File System (SPIFFS) with the specified configuration parameters.
 *
 * Notes :
 *   None
 **************************************************************************/
void init_file_system(void);
int P_delete_task(P_task_id_t *task_id);
#endif /* PLATFORM_ADAPTOR_H */
