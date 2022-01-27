#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>

TaskHandle_t HandleTask1, HandleTask2, HandleTask3, HandleTask4, HandleTask5

QueueHandle_t DataQueue;

void Task1(void *pv){
    while(1){
        printf("Task1 is running with periodicity 1000ms!!!\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void Task2(void *pv){
    while(1){
        printf("Task2 is running with periodicity 2000ms!!!\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void Task3(void *pv){
    while(1){
        printf("Task3 is running with periodicity 3000ms!!!\n");
        vTaskDelay(3000/portTICK_PERIOD_MS);
    }
}

void Task4(void *pv){
    int SendData=0;
    while(1){
    SendData++;
    printf("Task4 Data Sending: %d\n",SendData);
    xQueueSend(DataQueue, &SendData, portMAX_DELAY);
    vTaskDelay(500/portTICK_PERIOD_MS);
    if(SendData == 10)
    vTaskDelay(10000/portTICK_PERIOD_MS);
    }
}

void Task5(void *pv){
    int RecieveData=0;
    while(1){
    xQueueReceive(DataQueue, &RecieveData, portMAX_DELAY);
    printf("Task5 Data Received: %d\n",RecieveData);
    vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void app_main()
{
    BaseType_t T1, T2, T3, T4, T5;
    DataQueue = xQueueCreate(10, sizeof(int));
    T1 = xTaskCreate(Task1, "Task1", 2048, NULL, 5, &HandleTask1);
    if (T1 == pdPASS)
    {
        printf("Task 1 is created\n");
    }
    T2 = xTaskCreate(Task2, "Task2", 2048, NULL, 6, &HandleTask2);
    if (T2 == pdPASS)
    {
        printf("Task 2 is created\n");
    }
    T3 = xTaskCreate(Task3, "Task3", 2048, NULL, 7, &HandleTask3);
    if (T3 == pdPASS)
    {
        printf("Task 3 is created\n");
    }
    T4 = xTaskCreate(Task4, "Task4", 2048, NULL, 8, &HandleTask4);
    if (T4 == pdPASS)
    {
        printf("Task 4 is created\n");
    }
    T5 = xTaskCreate(Task5, "Task5", 2048, NULL, 9, &HandleTask5);
    if (T5 == pdPASS)
    {
        printf("Task 5 is created\n");
    }
}
