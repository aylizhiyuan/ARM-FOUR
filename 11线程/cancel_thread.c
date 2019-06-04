#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
void *thread_fun(void *arg){
    int stateval;
    int typeval;
    //首先将这个线程设置为不可以取消的状态
    stateval = pthread_setcancelstate(PTHREAD_CANCEL_DISABLE,NULL);
    if(stateval != 0){
        printf("set cancel state failure\n");
    }
    printf("i am new thread\n");
    sleep(4);//转到主线程

    //处理取消信号
    printf("about to cancel\n");
    stateval = pthread_setcancelstate(PTHREAD_CANCEL_ENABLE,NULL);
    if(stateval != 0){
        printf("set cancel state failed\n");
    };
    typeval = pthread_setcanceltype(PTHREAD_CANCEL_ASYNCHRONOUS,NULL);
    if(typeval != 0){
        printf("set cancel type failed\n");//立即取消
    }
    printf("first cancel point\n");//取消点
    printf("second cancel point\n");
    return (void *)20;
};
int main(){
    pthread_t tid;
    int err,cval,jval;
    void *rval;
    err = pthread_create(&tid,NULL,thread_fun,NULL);
    if(err != 0){
        printf("create thread failure\n");
        return 0;
    }
    sleep(2);//转到其他的线程上去
    //主线程继续执行
    cval = pthread_cancel(tid);//给线程发送取消信号
    if(cval != 0){
        printf("cancel thread failure\n");
    }
    jval = pthread_join(tid,&rval);//等待其他线程的结束
    printf("new thread exit code is %d\n",(int *)rval);
    return 0;
}