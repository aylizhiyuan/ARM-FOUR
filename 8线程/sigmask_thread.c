#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
//信号的处理函数
void sig_handler1(int arg){
    printf("thread1 get signal\n");
    return;
}
//信号的处理函数
void sig_handler2(int arg){
    printf("thread2 get sinal\n");
    return;
}
//线程的函数
void *thread_fun1(void *arg){
    printf("new thread 1\n");
    struct sigaction act;
    memset(&act,0,sizeof(act));
    //添加信号集
    sigaddset(&act.sa_mask,SIGQUIT);
    act.sa_handler = sig_handler1;
    //给信号注册一个处理的函数
    sigaction(SIGQUIT,&act,NULL);
    pthread_sigmask(SIG_BLOCK,&act.sa_mask,NULL);
    sleep(2);
};
void *thread_fun2(void *arg){
    printf("new thread 2\n");
    struct sigaction act;
    memset(&act,0,sizeof(act));
    //添加信号集
    sigaddset(&act.sa_mask,SIGQUIT);
    act.sa_handler = sig_handler2;
    sigaction(SIGQUIT,&act,NULL);
    //阻塞信号集
    pthread_sigmask(SIG_BLOCK,&act.sa_mask,NULL);
    sleep(2);
};
int main(){
    pthread_t tid1,tid2;
    int err;
    int s;
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
    sleep(1);

    //发出信号
    s = pthread_kill(tid1,SIGQUIT);
    if(s != 0){
        printf("send signal to thread1 failure\n");
    }
    //发出信号
    s = pthread_kill(tid2,SIGQUIT);
    if(s != 0){
        printf("send signal to thread2 failure\n");
    }
    //等待新线程运行
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    return 0;

}

