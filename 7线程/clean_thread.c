#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void *frist_clean(void *arg){
    printf("%s first clean\n",arg);
    return (void *)0;
};
void *second_clean(void *arg){
    printf("%s second clean\n",arg);
    return (void *)0;
};
void *thread_fun1(void *arg){
    printf("new thread 1\n");
    pthread_cleanup_push(frist_clean,"thread1");
    pthread_cleanup_push(second_clean,"thread1");
    pthread_cleanup_pop(1);
    pthread_cleanup_pop(0);
    return (void *)1;
};
void *thread_fun2(void *arg){
    printf("new thread 2\n");
    pthread_cleanup_push(frist_clean,"thread2");
    pthread_cleanup_push(second_clean,"thread2");
    pthread_cleanup_pop(0);
    pthread_cleanup_pop(0);
    pthread_exit((void *)2);
};
int main(){
    pthread_t tid1,tid2;
    int err;
    err = pthread_create(&tid1,NULL,thread_fun1,NULL);
    if(err != 0){
        printf("create new thread 1 failure\n");
        return 0;
    }
    err = pthread_create(&tid2,NULL,thread_fun2,NULL);
    if(err != 0){
        printf("create new thread 2 failure\n");
        return 0;
    }
    sleep(2);
}