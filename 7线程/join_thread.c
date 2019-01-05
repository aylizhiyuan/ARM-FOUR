#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void *thread_fun1(void *arg){
    printf("i am thread 1\n");
    return (void *)1;
};
void *thread_fun2(void *arg){
    printf("i am thread 2\n");
    pthread_detach(pthread_self());
    pthread_exit((void *)2);
};
int main(){
    int err1,err2;
    pthread_t tid1,tid2;
    void *rval1,*rval2;
    err1 = pthread_create(&tid1,NULL,thread_fun1,NULL);
    err2 = pthread_create(&tid2,NULL,thread_fun2,NULL);
    if(err1 || err2){
        printf("create new thread failure\n");
        return 0;
    }
    printf("i am main thread\n");
    //对两个线程进行连接
    //当前的主线程会等待两个线程结束后才会继续执行。rval是线程的返回代码
    printf("join1 rval is %d\n",pthread_join(tid1,&rval1));
    printf("join2 rval is %d\n",pthread_join(tid2,&rval2));
    printf("thread 1 exit code is %d\n",(int *)rval1);
    printf("thread 2 exit code is %d\n",(int *)rval2);
    return 0;
}

