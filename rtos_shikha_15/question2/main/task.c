#include<stdio.h>
#include"freertos/FreeRTOS.h"
#include"freertos/task.h"
#include"freertos/timers.h"

TaskHandle_t serial_task_handle,eth_task_handle,d_task_handle;
TimerHandle_t serial_timer_handle;
TimerHandle_t eth_timer_handle;
TimerHandle_t d_timer_handle;


void serial_timer_callback(TimerHandle_t serial_timer_handle)
{
    printf("timer fired\n");
}
void eth_timer_callback(TimerHandle_t eth_timer_handle)
{
    printf("timer fired\n");
}

void d_timer_callback(TimerHandle_t d_timer_handle)
{
    printf("timer fired\n");
}


void serial_task(void *data)
{
    printf("starting serial task\n");

    printf("creating the timer\n");
    serial_timer_handle=xTimerCreate("one_s_timer",1000/portTICK_PERIOD_MS,pdFALSE,0,serial_timer_callback);
    xTimerStart(serial_timer_handle,0);
    vTaskDelete(serial_task_handle);
    
}
void eth_task(void *data)
{
    printf("starting eth task\n");
    printf("creating the timer\n");
   eth_timer_handle=xTimerCreate("one_s_timer",2000/portTICK_PERIOD_MS,pdFALSE,0,eth_timer_callback);
    xTimerStart(eth_timer_handle,0);
    vTaskDelete(eth_task_handle);
}


void d_task(void *data)
{
    printf("starting d task\n");
    printf("creating the timer\n");
    d_timer_handle=xTimerCreate("one_s_timer",5000/portTICK_PERIOD_MS,pdTRUE,0,d_timer_callback);
    xTimerStart(d_timer_handle,0);
    vTaskDelete(d_task_handle);
}





void app_main()
{
    printf("DESD RTOS\n");
    xTaskCreate(serial_task,"serial priority",2048,NULL,5,&serial_task_handle);
    xTaskCreate(eth_task,"eth priority",2048,NULL,6,&eth_task_handle);
    xTaskCreate(d_task,"d priority",2048,NULL,7,&d_task_handle);
}