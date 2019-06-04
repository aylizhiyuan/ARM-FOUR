#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void print_id(char *s){
    pid_t pid;
    pthread_t tid;
    pid = getpid();
    tid = pthread_self();
    printf("%s pid is %u,tid is 0x%x\n",s,pid,tid);
}
void *thread_fun(void *arg){
  print_id(arg);
  return (void *)0;  
}
int main(){
    pthread_t ntid;
    int err;
    //创建线程
    err = pthread_create(&ntid,NULL,thread_fun,"new thread");
    if(err != 0){
        printf("create new thread failed\n");
        return 0;
    }
    //打印主线程
    print_id("main thread:");
    sleep(2);
    return 0;
}