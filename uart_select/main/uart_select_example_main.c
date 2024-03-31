#include <stdio.h>
#include <sys/fcntl.h>
#include <sys/errno.h>
#include <sys/unistd.h>
#include <sys/select.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_log.h"
#include "esp_vfs.h"
#include "esp_vfs_dev.h"
#include "driver/uart.h"

static const char *TAG = "5GVPN";

#define UART_NUM UART_NUM_0

void handle_user_option(int command)
{
    switch (command)
    {
    case 1:
        ESP_LOGI(TAG, "Registeration Request initiated\n");
        // Handle case 1: Registration initiated
        // Code to handle case 1 goes here
        break;

    case 2:
        ESP_LOGI(TAG, "PDU Session Establishment Request\n");
        // Handle case 2: PDU session establishment request
        // Code to handle case 2 goes here
        break;

    case 3:
        ESP_LOGI(TAG, "PDU Session Modify Request\n");
        // Handle case 3: PDU session modification request
        // Code to handle case 3 goes here
        break;

    case 4:
        ESP_LOGI(TAG, "PDU Session Release Request\n");
        // Handle case 4: PDU session release
        // Code to handle case 4 goes here
        break;

    case 5:
        ESP_LOGI(TAG, "Sending message on PDU Session Established\n");
        // Handle case 5: Sending message on PDU session established
        // Code to handle case 5 goes here
        break;

    case 6:
        ESP_LOGI(TAG, "Stopping the 5GVPN Stack & Exiting\n");
        // Handle case 6: Stop and exit
        // Code to handle case 6 goes here
        break;

    default:
        ESP_LOGW(TAG, "Invalid command: %d", command);
        break;
    }
}

static void uart_select_task(void *arg)
{
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE,
        .source_clk = UART_SCLK_APB,
    };
    uart_driver_install(UART_NUM_0, 2 * 1024, 0, 0, NULL, 0);
    uart_param_config(UART_NUM_0, &uart_config);

    int fd;

    if ((fd = open("/dev/uart/0", O_RDWR)) == -1)
    {
        ESP_LOGE(TAG, "Cannot open UART");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
        vTaskDelete(NULL);
        return;
    }

    // We have a driver now installed, so set up the read/write functions to use the driver also.
    esp_vfs_dev_uart_use_driver(0);

    while (1)
    {
        // Print the menu options
        ESP_LOGI(TAG, "Please enter a command from the list below:\n");
        ESP_LOGI(TAG, "1 - Registration Request");
        ESP_LOGI(TAG, "2 - PDU Session Establishment Request");
        ESP_LOGI(TAG, "3 - PDU Session Modify Request");
        ESP_LOGI(TAG, "4 - PDU Session Release Request");
        ESP_LOGI(TAG, "5 - Send message on PDU Session Established");
        ESP_LOGI(TAG, "6 - Stop the 5GVPN Stack & Exit");

        int s;
        fd_set rfds;
        struct timeval tv = {
            .tv_sec = 60,
            .tv_usec = 0,
        };

        FD_ZERO(&rfds);
        FD_SET(fd, &rfds);

        s = select(fd + 1, &rfds, NULL, NULL, &tv);

        if (s < 0)
        {
            ESP_LOGE(TAG, "Select failed: errno %d", errno);
            break;
        }
        else if (s == 0)
        {
            ESP_LOGI(TAG, "Timeout has been reached and nothing has been from user");
        }
        else
        {
            if (FD_ISSET(fd, &rfds))
            {
               
                uint8_t count = 0;

                char buf[10] = {0}; 

                while ((count <= 10) || buf[count] == '\n')
                {
                    
                    if (read(fd, &buf[count], 1) > 0)
                    {
                       
                        if (buf[count] == '\n')
                        {
                            printf("\n");
                            
                            int option = atoi(buf);
                            if (option <= 10)
                            {
                                ESP_LOGI(TAG,"Handling required function-%d\n",option);
                                handle_user_option(option);
                                break;
                            }else{
                                ESP_LOGE(TAG,"Invalid input\n");
                            }
                        }
                        else{
                            printf("%c",buf[count]);
                            fflush(stdout);

                        }
                        count++;
                    }
                    else
                    {
                        ESP_LOGE(TAG, "UART read error");
                        break;
                    }
                }
            }
            else
            {
                ESP_LOGE(TAG, "No FD has been set in select()");
                break;
            }
        }
    }

    close(fd);
    vTaskDelete(NULL);
}

void app_main(void)
{
    xTaskCreate(uart_select_task, "uart_select_task", 4 * 1024, NULL, 5, NULL);
}
