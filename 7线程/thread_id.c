#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
int main(){
    pid_t pid;
    pthread_t tid;
    pid = getpid();//获取进程的ID
    tid = pthread_self();//获取线程的ID
    printf("pid=%u,tid=%u\n",pid,tid);
    return 0;
}

