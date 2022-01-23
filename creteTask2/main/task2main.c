#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
//#include<FreeRTOSConfig.h>

//Handle for the Task which we have created
TaskHandle_t xHandleTaskLog1, xHandleTaskLog2;

//Function that create Task1
void TaskLog(void *pvParameters)
{
    int array[10];

    printf("Inside the TaskLog1 function....\n");

    for(int i=0; i<10; i++)
    {
        array[i] = i;
        printf("array[%d] = %d\n",i, array[i]);
    }

    vTaskDelete(xHandleTaskLog1);   // or we can use this also >>> vTaskDelete(NULL);

}

//Function that Creates Task2
void TaskLog2(void *pvParameters)
{
    int arr[10];

    printf("Inside the TaskLog2 function.....\n");

    for(int i=10; i>=0; i--)
    {
        arr[i] = i;
        printf("arr[%d] = %d\n",i, arr[i]);
    }

    vTaskDelete(xHandleTaskLog2);    

}


void app_main()
{
    BaseType_t xTask_fd1, xTask_fd2;

    //To Create Task
    xTask_fd1 = xTaskCreate(TaskLog, "TaskLog", 2048, NULL, 5, &xHandleTaskLog1);
    xTask_fd2 = xTaskCreate(TaskLog2, "TaskLog2",2048, NULL, 6, &xHandleTaskLog2);

    if(xTask_fd1 == pdPASS){
        printf("TaskLog1 is created successfully\n");
    }

    if(xTask_fd2 == pdPASS){
        printf("TaskLog2 is created successfully\n");
    }

}