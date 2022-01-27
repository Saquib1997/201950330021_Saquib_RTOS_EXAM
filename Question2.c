#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <stdio.h>
#include <freertos/timers.h>

BaseType_t T1;
BaseType_t T2;
BaseType_t T3;
TaskHandle_t HandleTask1;
TaskHandle_t HandleTask2;
TaskHandle_t HandleTask3;

TimerHandle_t OneShotTimer;

void Task1(void *pv)
{
    while (1)
    {
        printf("Task 1 is Running!!!\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void Task2(void *pv)
{
    while (1)
    {
        printf("Task 2 is Running!!!\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void Task3(void *pv)
{
    while (1)
    {
        printf("Task 3 is Running!!!\n");

        void OneShotCallback(TimerHandle_t xTimer);
        {
            printf("One Shot Timer is called and this function signing off!!!\n");
        }
        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}
void OneShotCallback(TimerHandle_t xTimer)
{
    printf("Function is expired and One Shot is called\n");
}

void app_main()
{
    T1 = xTaskCreate(Task1, "Task 1 ", 2048, NULL, 5, &HandleTask1);
    if (T1 == pdPASS)
    {
        printf("Task 1 is created succesfully\n");
    }

    T2 = xTaskCreate(Task2, "Tasks 2 ", 2048, NULL, 6, &HandleTask2);
    if (T2 == pdPASS)
    {
        printf("Task 2 is created succesfully\n");
    }

    T3 = xTaskCreate(Task3, "Tasks 3 ", 2048, NULL, 7, &HandleTask3);
    if (T3 == pdPASS)
    {
        printf("Task 3 is created succesfully\n");
    }

    OneShotTimer = xTimerCreate("Autoreload", pdMS_TO_TICKS(10000), pdFALSE, NULL, OneShotTimer);
    xTimerStart(OneShotTimer, 0);

    while (1)
    {
        printf("Main Task is Running!!!\n");
        vTaskDelay(500/portTICK_PERIOD_MS);
    }
}
