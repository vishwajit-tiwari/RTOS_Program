#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/semphr.h>
#include<freertos/task.h>
#include<FreeRTOSConfig.h>
#include<freertos/timers.h>



//Handle for the Task which we have created
TaskHandle_t xHandleTaskLog;

//Function that create Task
void TaskLog(void *pvParameters)
{
    int array[10];

    printf("Inside the TaskLog function....\n");

    for(int i=0; i<10; i++)
    {
        array[i] = i;
        printf("array[%d] = %d\n", i, array[i]);
    }

    vTaskDelete(xHandleTaskLog);   // or we can use this also >>> vTaskDelete(NULL);

}


void app_main()
{
    BaseType_t xTask_fd;

    //To Create Task
    xTask_fd = xTaskCreate(TaskLog, "TaskLog", 2048, NULL, 5, &xHandleTaskLog);

    if(xTask_fd == pdPASS){
        printf("TaskLog is created successfully\n");
    }

}