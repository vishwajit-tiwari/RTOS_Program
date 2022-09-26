/**
 * @file taskmain.c
 * @author your name (you@domain.com)
 * @brief A multitasking system with Message Queue
 * @version 0.1
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include<stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/FreeRTOSConfig.h>
#include<freertos/task.h>
#include<freertos/queue.h>

// Task Handle : To handle the different task
TaskHandle_t task1Handle, task2Handle, task3Handle, task4Handle, task5Handle;
// For Message Queue Create
QueueHandle_t queueHanlde;
UBaseType_t QueueLength = 10;
UBaseType_t ItemSize = sizeof(int);
// For Queue Send
BaseType_t retQueueSend, retQueueReceive;


/**********************************Task-1*********************************/
void Task1(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 1000ms
    const TickType_t xDelay = 1000 / portTICK_PERIOD_MS;

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task1 : running...\n");
        // To provide delay
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task1Handle);
}
/**************************************************************************/

/****************************Task-2****************************************/ 
void Task2(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 2000ms
    const TickType_t xDelay = 2000 / portTICK_PERIOD_MS;
    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task2 : running...\n");
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task2Handle);
}
/*************************************************************************/

/******************************Task-3**************************************/ 
void Task3(void * parameter) 
{
    printf("Inside %s():\n", __FUNCTION__);

    // Block for 5000ms
    const TickType_t xDelay = 5000 / portTICK_PERIOD_MS;

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        printf("Task3 : running....\n");
        // To provide delay
        vTaskDelay(xDelay);
    }

    // To delete task
    vTaskDelete(task3Handle);
}
/***************************************************************/

/***************************Task-4*******************************/ 
void Task4(void * parameter) 
{
    int num = 0;

    printf("Inside %s():\n", __FUNCTION__);

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        retQueueSend = xQueueSend(queueHanlde, (const void *)&num, (TickType_t)10);
        if(retQueueSend == errQUEUE_FULL) {
            perror("error in QueueSend : ");
            exit(EXIT_FAILURE);
        }
        else if(retQueueSend == pdTRUE) {
            printf("Item sent : success\n");
            num++;
        }
    }

    // To delete task
    vTaskDelete(task4Handle);
}
/****************************************************************/

/****************************Task-5******************************/ 
void Task5(void * parameter) 
{
    int num = 0;

    printf("Inside %s():\n", __FUNCTION__);

    // For parameter
    configASSERT(((uint32_t *)parameter) == NULL);

    for(;;) 
    {
        retQueueReceive = xQueueReceive(queueHanlde, &num, 10);
        if(retQueueReceive == pdFALSE) {
            perror("error in Message Queue Receive: \n");
            exit(EXIT_FAILURE);
        }
        else if (retQueueReceive == pdTRUE) {
            printf("Item receive : success\n");
            printf("Item : %d\n", num);
        }
    }

    // To delete task
    vTaskDelete(task5Handle);
}
/*****************************************************************/



void app_main()
{
    BaseType_t task1Return, task2Return, task3Return, task4Return, task5Return;

    printf("Inside %s() function:\n", __FUNCTION__);

    /**xTaskCreate(Pointer to the task entry function,
     *              A descriptive name for the task,
     *              Stack size, Parameter, Priority, Task handler)*/
    
    task1Return = xTaskCreate(Task1, "Task1", 2048, NULL, 5, &task1Handle);
    if(task1Return != pdPASS) {
        perror("error in task1 ");
        exit(EXIT_FAILURE);
    }
    printf("Task1 : created\n");

    task2Return = xTaskCreate(Task2, "Task2", 2048, NULL, 6, &task2Handle);
    if(task2Return != pdPASS) {
        perror("error in task2 ");
        exit(EXIT_FAILURE);
    }
    printf("Task2 : created\n");

    task3Return = xTaskCreate(Task3, "Task3", 2048, NULL, 7, &task3Handle);
    if(task3Return != pdPASS) {
        perror("error in task3 ");
        exit(EXIT_FAILURE);
    }
    printf("Task3 : created\n");

    task4Return = xTaskCreate(Task4, "Task4", 2048, NULL, 8, &task4Handle);
    if(task4Return != pdPASS) {
        perror("error in task4 ");
        exit(EXIT_FAILURE);
    }
    printf("Task4 : created\n");

    task5Return = xTaskCreate(Task5, "Task5", 2048, NULL, 9, &task5Handle);
    if(task5Return != pdPASS) {
        perror("error in task5 ");
        exit(EXIT_FAILURE);
    }
    printf("Task5 : created\n");

    // To create Message Queue
    queueHanlde = xQueueCreate(QueueLength,ItemSize);
    if(queueHanlde == NULL) {
        perror("error in Message Queue : ");
        exit(EXIT_FAILURE);
    }
    printf("Message Queue : Created\n");

}