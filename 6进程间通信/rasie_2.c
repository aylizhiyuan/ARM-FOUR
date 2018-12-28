#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
int main(){
    pid_t pid;
    pid =fork();
    if(pid > 0){
        //父进程进入睡眠 状态
        sleep(8);
        //在父进程中等待子进程，子因为处于暂停状态，因而杀死子进程
        if(waitpid(pid,NULL,WNOHANG) == 0){
            kill(pid,9);
        }
        while(1);
    }
    if(pid == 0){
        //子进程进程暂停状态
        printf("raise function before\n");
        raise(SIGTSTP);
        printf("raise function after\n");
        exit(0);
    }
    return 0;
}