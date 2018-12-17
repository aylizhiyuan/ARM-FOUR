#include <sys/types.h>
#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

static int alarm_fired = 0;
void ding(int sig){
    alarm_fired = 1;
}
//在main函数中，我们告诉子进程在等待5秒后发送一个sigalrm信号给它的父进程
int main(){
    pid_t pid;
    printf("alarm application starting\n");
    pid = fork();
    switch(pid){
        case -1: 
            perror("Fork failed");
            exit(1);
        case 0: 
            sleep(5);
            //把信号发送给指定的进程
            kill(getppid(),SIGALRM);
            exit(0);
    }
    //父进程通过一个signal调用安排好sigalrm信号的工作
    //然后等待它的到来
    printf("waiting for alarm parent process");
    (void)signal(SIGALRM,ding);
    pause();
    if(alarm_fired){
        printf("Ding!\n");
    }
    printf("Done\n");
    exit(0);
}

