/**
 * @file taskmain.c
 * @author your name (you@domain.com)
 * @brief A multitasking system with Oneshot Software Timer
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
#include<freertos/timers.h>

//Task Handle : To handle the different task
TaskHandle_t task1Handle, task2Handle, task3Handle, task4Handle, task5Handle;
//Handle for Timer
TimerHandle_t retTimerCreate;


/************************Timer callback function***************************/
void TimerCallback(TimerHandle_t xTimer) 
{
    printf("Inside %s() function : \n", __FUNCTION__);

    printf("Timer triggered\n");

    const uint32_t MaxExpiryCountBeforeStopping = 10;
    uint32_t Count;

    //Optionally do something if pxTimer parameter is NULL
    configASSERT(xTimer);

    //The number of time the timer is expired
    Count = (uint32_t)pvTimerGetTimerID(xTimer);

    // Increment and test to see if timer is expired
    Count++;

    // If the timer is expired 10 times then stop it from running 
    if(Count>=MaxExpiryCountBeforeStopping) {
        printf("Timer Expire : 10 times : Stopping it now...\n");
        xTimerStop(xTimer,0);
    }
    else {
        vTimerSetTimerID(xTimer,(void*)Count);
    }

}
/**************************************************************************/


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

    //One Shot Software Timer
    retTimerCreate = xTimerCreate("One shot software Timer", pdMS_TO_TICKS(10000), pdFALSE, (void*)0, TimerCallback);
    if(retTimerCreate == NULL) {
        perror("error in timer creation ");
        exit(EXIT_FAILURE);
    }
    printf("Timer started......\n");
    
    //Start Timer
    xTimerStart(retTimerCreate,0);

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



void app_main()
{
    BaseType_t task1Return, task2Return, task3Return;

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

}