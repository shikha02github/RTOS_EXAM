#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/queue.h"
#include"freertos/task.h"


#define MQ_SIZE 4
#define MSG_SIZE 64

TaskHandle_t task1_handle,task2_handle,task3_handle,task4_handle,task5_handle;
QueueHandle_t msg_queue;
static int taskcore = 1;

void task_1(void *data)
{
    int task1_data = 100;
    printf("Task 1\n");
    while(1)
    {
        task1_data++;
        xQueueSend(msg_queue, &task1_data, pdMS_TO_TICKS(1000));
        vTaskDelay(1000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}


void task_2(void *data)
{
    int task2_data = 200;
    printf("Task 2\n");
    while(1)
    {
        task2_data++;
        xQueueSend(msg_queue, &task2_data, pdMS_TO_TICKS(2000));
        vTaskDelay(2000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);

    

}

void task_3(void *data)
{
    int task3_data = 300;
    printf("Task 3\n");
    while(1)
    {
        task3_data++;
        xQueueSend(msg_queue, &task3_data, pdMS_TO_TICKS(5000));
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task_4(void *data)
{
    int buffer = 0;
    printf("Task 4\n");
    while(1)
    {
        xQueueReceive(msg_queue, &buffer, portMAX_DELAY);
        printf("task 4 :send data:%d\n",buffer);
    }
    vTaskDelete(NULL);
}


void task_5(void *data)
{
    int buffer = 0;
    int count = 0;
    printf("Task 5\n");
    while(1)
    {
        xQueueReceive(msg_queue, &buffer, portMAX_DELAY);
        printf("Task 5:Receive Data :%d\n",buffer);
        count ++;
        if(count>10)
        {
            count = 0;
            vTaskDelay(7000 / portTICK_PERIOD_MS);
        }
        
    }
    vTaskDelete(NULL);
}

void app_main()
{
    printf("Main Task\n");
    msg_queue = xQueueCreate(MQ_SIZE, MSG_SIZE);
    xTaskCreatePinnedToCore(task_1, "First Task", 2048,NULL,5, &task1_handle,taskcore);
    xTaskCreatePinnedToCore(task_2, "Second Task", 2048,NULL,6, &task1_handle,taskcore);
    xTaskCreatePinnedToCore(task_3, "Third Task" , 2048,NULL,7, &task3_handle,taskcore);
    xTaskCreatePinnedToCore(task_4, "Fourth Task" , 2048,NULL,8,&task4_handle,taskcore);
    xTaskCreatePinnedToCore(task_5, "Fifth Task" , 2048,NULL, 9,&task5_handle,taskcore);
}




