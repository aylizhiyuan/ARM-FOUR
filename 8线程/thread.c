#include "stdio.h"
#include "stdlib.h"
#include "pthread.h"
//子线程打印10条语句
void *fun(void *var){
    int j;
    for(j=0;j<10;j++){
        usleep(100);
        printf("this is fun j=%d\n",j);
    }
}
int main(){
    //可以理解为mian函数就是主线程
    int i;
    char str[] = "hello world\n";
    pthread_t tid;
    int ret;
    ret = pthread_create(&tid,NULL,fun,(void *)str);
    if(ret < 0){
        printf("create thread failure\n");
        return -1;
    }
    for(i=0;i<10;i++){
        usleep(100);
        printf("this is main fun i=%d\n",i);
    }
    while(1);
    return 0;
}