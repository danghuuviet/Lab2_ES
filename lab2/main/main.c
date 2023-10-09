#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"

#define STUDENT_IDENTIFIER "2013783"

// Function for the cyclic task
void cyclic_task(void *pvParameters)
{
    while (1)
    {
        printf("%s\n", STUDENT_IDENTIFIER);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// Function for the acyclic task
void acyclic_task(void *pvParameters)
{
    // Initialize the GPIO button (assuming you have a button connected to GPIO)
    // gpio_pad_select_gpio(GPIO_NUM_34);
    esp_rom_gpio_pad_select_gpio(GPIO_NUM_17);
    gpio_set_direction(GPIO_NUM_17, GPIO_MODE_INPUT);
    gpio_set_pull_mode(GPIO_NUM_17, GPIO_PULLUP_ONLY);

    while (1)
    {
        if (gpio_get_level(GPIO_NUM_17) == 0)
        { // Button is pressed (assuming active low)
            printf("ESP32\n");
            vTaskDelay(pdMS_TO_TICKS(100)); // Delay for debouncing (adjust as needed)
        }
        vTaskDelay(pdMS_TO_TICKS(10)); // Poll the button every 10 milliseconds
    }
}

void app_main()
{

    xTaskCreate(cyclic_task, "Cyclic Task", 2048, NULL, 1, NULL);

    xTaskCreate(acyclic_task, "Acyclic Task", 2048, NULL, 2, NULL);
}