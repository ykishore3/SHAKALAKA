#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
int count = 0,n=50;
pthread_mutex_t mutex=PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t cond= PTHREAD_COND_INITIALIZER;
void *printEvenNum(void *arg)
{   
    while(count < n)
    {
        pthread_mutex_lock(&mutex);
        while(count % 2 != 0)
        {   
            pthread_cond_wait(&cond, &mutex);
        }
        printf("even:-%d\n", count++);
//sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
}
void *printOddNum(void *arg)
{   
    while(count < n)
    {
        pthread_mutex_lock(&mutex);
        while(count % 2 != 1)
        {   
            pthread_cond_wait(&cond, &mutex);
        }
        printf("odd:-%d\n", count++);
//sleep(1);
        pthread_mutex_unlock(&mutex);
        pthread_cond_signal(&cond);
    }
}
int main()
{
    pthread_t thread1;
    pthread_t thread2;
    pthread_mutex_init(&mutex, 0);
    pthread_cond_init(&cond, 0);
    pthread_create(&thread1, 0, &printEvenNum, NULL);
    pthread_create(&thread2, 0, &printOddNum, NULL);
    pthread_join(thread1, 0);
    pthread_join(thread2, 0);
    pthread_mutex_destroy(&mutex);
    pthread_cond_destroy(&cond);
    return  0;
}

