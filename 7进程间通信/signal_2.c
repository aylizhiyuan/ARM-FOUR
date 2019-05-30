#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
void myfun(int signum){
    int i;
    i=0;
    while(i<10){
        printf("process signal signum=%d\n",signum);
        sleep(1);
        i++;
    }
    return;
}
int main(){
    int i;
    i=0;
    signal(14,myfun);
    printf("alarm before\n");
    alarm(9);
    printf("alarm after\n");
    signal(14,SIG_IGN);//处理器会按照最新的处理方式
    signal(14,SIG_DFL);//默认方式处理
    while(i<20){
        i++;
        sleep(1);
        printf("process things,i=%d\n",i);
    }
    return 0;
}