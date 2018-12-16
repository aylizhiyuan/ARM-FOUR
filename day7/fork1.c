#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    pid_t pid;
    char *message;
    int n;
    printf("for program starting\n");
    pid = fork();
    //如果是父进程的话，则返回新进程的PID
    //如果是子进程的话，则返回0
    //通过这个我们就可以判断当前的进程是父进程还是子进程
    switch(pid){
        case -1:
            perror("fork failed");
            exit(1);
        case 0:
            message = "this is the child";
            n = 5;
            break;
        default: 
            message = "this is the parent";
            n = 3;
            break;
    }
    for(;n>0;n--){
        puts(message);
        sleep(1);
    }
    exit(0);
}
//这个程序以两个进程的形式在运行。子进程被创建并且输出五次
//父进程只输出消息三次，父进程在子进程打印完他的全部消息
//之前就结束了