#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
int main(){
    pid_t pid;
    pid = fork();
    
    ///在子进程中，pid的返回值是0
    if(pid == 0){
        //子进程
        int i=0;
        for(i=0;i<5;i++){
            printf("this is child process i=%d\n",i);
            usleep(100);
        }
    }
    //在父进程中，pid的返回值应该是子进程的PID
    if(pid > 0){
        int i=0;
        for(i=0;i<5;i++){
            printf("this is parent process i=%d\n",i);
            usleep(100);
        }
    }
    while(1);
    return 0;
}
//在一般情况下，父子进程是没有任何交流的，都是单独运行的程序。
//你可以理解为创建进程就是通过代码的方式创建一个即将要运行的程序