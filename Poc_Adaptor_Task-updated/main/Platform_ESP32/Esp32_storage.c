#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "freertos/timers.h"
#include <string.h>
#include <sys/unistd.h>
#include <sys/stat.h>
#include "esp_err.h"
#include "esp_log.h"
#include "esp_spiffs.h"
#include "../Platform_Adaptor/Platform_Adaptor.h"
#include "esp_vfs.h"
#include "esp_vfs_fat.h"

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

void init_file_system()
{

    P_printf("Initializing VFS\n");

    esp_vfs_spiffs_conf_t conf = {
        .base_path = "/spiffs",
        .partition_label = NULL,
        .max_files = 5,
        .format_if_mount_failed = true};
    esp_err_t ret = esp_vfs_spiffs_register(&conf);

    if (ret != ESP_OK)
    {
        if (ret == ESP_FAIL)
        {
            P_printf("Failed to mount or format filesystemi\n");
        }
        else if (ret == ESP_ERR_NOT_FOUND)
        {
            printf("Failed to find partition\n");
        }
        else
        {
            P_printf("Failed to initialize VFS (%s)", esp_err_to_name(ret));
        }
    }
}

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
P_file_t P_fopen(const char *file_name, const char *mode_of_operation)
{

    FILE *file_return;
    file_return = fopen(file_name, mode_of_operation);
    if (file_return == NULL)
    {
        P_printf("Failed to open file \n");
    }
    return file_return;
}

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

size_t P_fwrite(const void *ptr, size_t size, size_t count, P_file_t *file)
{
    if (file == NULL)
    {
        P_printf("Invalid file pointer\n");
        return 0;
    }
    return fwrite(ptr, size, count, (FILE *)file);
}

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

size_t P_fread(void *ptr, size_t size, size_t nmemb, P_file_t *file)
{
    if (file == NULL)
    {
        P_printf("Invalid file pointer\n");
        return 0;
    }
    return fread(ptr, size, nmemb, (FILE *)file);
}

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

char P_fgets(char *str, int n, P_file_t *file)
{
    if (file == NULL)
    {
        P_printf("Invalid file pointer\n");
        return NULL;
    }
    return fgets(str, n, (FILE *)file);
}

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

int P_fclose(P_file_t *file)
{
    if (file == NULL)
    {
        P_printf("Invalid file pointer\n");
        return EOF;
    }
    int result = fclose((FILE *)file);
    return result;
}
