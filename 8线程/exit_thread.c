#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void *thread_fun(void *arg){
    if(strcmp("1",(char *)arg) == 0){
        printf("new thread return!\n");
        return (void *)1;//不会导致主线程的退出
    }
    if(strcmp("2",(char *)arg) == 0){
        printf("new thread pthread_eixt!\n");
        pthread_exit((void *)2);//不会导致主线程的退出
    }
    if(strcmp("3",(char *)arg) == 0){
        printf("new thread exit\n");
        exit(3);//会导致主 线程的退出
    }
};
int main(int argc,char *argv[]){
    int err;
    pthread_t tid;
    err = pthread_create(&tid,NULL,thread_fun,(void *)argv[1]);
    if(err != 0){
        printf("create new thread failure\n");
        return 0;
    }
    sleep(1);
    printf("main thread\n");
    return 0;
}