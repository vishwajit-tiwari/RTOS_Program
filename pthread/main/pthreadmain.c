#include <stdio.h>
#include<pthread.h>

//Function for Posix-Thread

void *helloESP32Thread(void *arg)
{
    printf("Inside Thread Function!\n");
    return NULL;
}

void app_main()
{
    pthread_t thread_id;

    printf("Hello C-DAC\n");

//To create Posix-Thread

    pthread_create(&thread_id, NULL, helloESP32Thread, NULL);
    pthread_join(thread_id, NULL);
}

