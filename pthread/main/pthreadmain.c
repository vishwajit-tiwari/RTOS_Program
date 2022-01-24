#include <stdio.h>
#include<pthread.h>
#include<semaphore.h>

sem_t s1, s2;   //Semaphore arguments

//Function for Posix-Thread-1

void *helloESP32Thread(void *arg)
{
    while(1)
    {
        sem_wait(&s1);
        printf("Inside 1st Thread...\n");
        printf("Enter two numbers: ");
        scanf("%d %d", &num1, &num2);
    }
    return NULL;
}

//Function for Posix-Thread-1

void *hiESP32Thread(void *arg)
{
    while(1)
    {
    printf("Inside 2nd Thred...\n");
    }
    return NULL;
}


void app_main()
{
    pthread_t thread_id1, thread_id2;

    printf("Hi Welcome to thread programming....\n");

//To create Posix-Thread

    pthread_create(&thread_id1, NULL, helloESP32Thread, NULL);
    pthread_create(&thread_id2, NULL, hiESP32Thread, NULL);
    
    pthread_join(thread_id1, NULL);
    pthread_join(thread_id2, NULL);

}

