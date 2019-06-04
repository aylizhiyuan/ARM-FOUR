#include "sys/types.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(int argc,char *argv[]){
    int sig;
    int pid;
    if(argc < 3){
        //命令行参数至少是两个
        printf("please input param\n");
        return -1;
    }
    //信号的值
    sig = atoi(argv[1]);//转化成整数
    pid = atoi(argv[2]);//进程的值
    printf("sig=%d,pid=%d\n",sig,pid);
    //kill来进行杀死进程
    kill(pid,sig);
    return 0;
}
//自己写一个自定义的kill命令