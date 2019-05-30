#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
//声明一个读写锁
pthread_rwlock_t rwlock;
int num = 0;
void *thread_fun1(void *arg){
    int err;
    //加一个读锁
    pthread_rwlock_rdlock(&rwlock);
    printf("thread 1 print num %d\n",num);
    //这个线程休眠五秒钟
    sleep(5);
    printf("thread 1 over\n");
    //解锁
    pthread_rwlock_unlock(&rwlock);
    return (void *)1;
}
void *thread_fun2(void *arg){
    int err;
    //加锁
    pthread_rwlock_rdlock(&rwlock);
    printf("thread 2 printf num %d\n",num);
    sleep(5);
    printf("thread 1 over\n");
    //解锁
    pthread_rwlock_unlock(&rwlock);
    return (void *)1;
}
int main(){
    pthread_t tid1,tid2;
    int err;
    //初始化读写锁
    pthread_rwlock_init(&rwlock,NULL);
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
    pthread_join(tid1,NULL);
    pthread_join(tid2,NULL);
    //销毁读写锁
    pthread_rwlock_destroy(&rwlock);
    return 0;
}