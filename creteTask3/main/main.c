#include <stdio.h>
#include<stdlib.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include<freertos/timers.h>
#include<freertos/message_buffer.h>
#include<freertos/queue.h>
#include<freertos/semphr.h>
#include<FreeRTOSConfig.h>

//Task Handles
TaskHandle_t userTask1_handle1, userTask2_handle2;



//----Function that implements the task-1------//

void userTask1(void *pvParameters)
{
    int array[10];

    printf("Inside Task-1 function....!\n");

    /* The parameter value is expected to be 1 as 1 is passed in the
    pvParameters value in the call to xTaskCreate() below.*/
    configASSERT(( (uint32_t) pvParameters ) == 1);

    for(int i = 0; i < 10; i++)
    {
        array[i] = i;
        printf("array[%d] = %d\n", i, array[i]);
    }

    //To delete task    
    vTaskDelete(userTask1_handle1);
}
//----------------------------------------------//


//----Function that implements the task-2------//

void userTask2(void *pvParameters)
{
    int Array[10];

    printf("Inside Task-2 function....!\n");

    /* The parameter value is expected to be 2 as 2 is passed in the
    pvParameters value in the call to xTaskCreate() below.*/
    configASSERT(( (uint32_t) pvParameters ) == 2);

    for(int i = 20; i > 10; i--)
    {
        Array[i] = i;
        printf("array[%d] = %d\n", i, Array[i]);
    }

    //To delete task    
    vTaskDelete(userTask2_handle2);
}
//----------------------------------------------//




void app_main(void)
{
    BaseType_t Task1_return, Task2_return;

    printf("Welcome to ESP32 Programming....!\n");

    //API for Task creation

    Task1_return = xTaskCreate(userTask1, "userTask-1", 2048, (void *)1, 3, &userTask1_handle1);
    Task2_return = xTaskCreate(userTask2, "userTask-2", 2048, (void *)2, 5, &userTask2_handle2);

    if(Task1_return == pdPASS)
    {
        printf("Task-1 created sucessfully\n");

    }
    else if(Task1_return == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
        printf("Can not create Task-1!\n");
        perror("Task-1 not created ");
        exit(EXIT_FAILURE);
    }
    
    if(Task2_return == pdPASS)
    {
        printf("Task-2 created sucessfully\n");
    }
    else if(Task2_return == errCOULD_NOT_ALLOCATE_REQUIRED_MEMORY)
    {
        printf("Can not create Task-2...!\n");
        perror("Task-2 not created ");
        exit(EXIT_FAILURE);
    }

}

