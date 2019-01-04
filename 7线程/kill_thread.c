#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void *thread_fun(void *arg){
    sleep(1);
    printf("i am new thread\n");
    return (void *)0;
};
int main(){
    pthread_t tid;
    int err;
    int s;
    void *rval;
    err = pthread_create(&tid,NULL,thread_fun,NULL);
    if(err != 0){
        printf("create new thread failed\n");
        return 0;
    }
    //sleep(1);
    s = pthread_kill(tid,SIGQUIT);//默认是终止这个线程,sigquit是退出，如果没有对应的处理函数则会终止该进程
    if(s == ESRCH){
        printf("thread tid is not found\n");
    }
    pthread_join(tid,&rval);
    printf("i am main thread\n");
    return 0;
}