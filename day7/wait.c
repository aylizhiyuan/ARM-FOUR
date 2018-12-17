#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    pid_t pid;
    char *message;
    int n;
    int exit_code;
    printf("fork program starting\n");
    pid = fork();
    switch(pid){
        case -1: 
            perror("fork failed");
            exit(1);
        case 0: 
            message = "this is the child";
            n = 5;
            exit_code = 37;
            break;
        default: 
            message = "this is the parent";
            n = 3;
            exit_code = 0;
            break;
    }
    //循环开始
    for(;n>0;n--){
        puts(message);
        sleep(1);
    }
    //程序这部分等待子进程完毕
    if(pid != 0){
        int stat_val;
        pid_t child_pid;
        //父进程用wait系统调用将自己的执行挂起，直到子进程
        //的状态信息出现为止。这将发生在子进程调用exit的时候
        //我们将子进程的退出码设置为37，父进程然后继续运行
        //通过测试wait调用的返回值来判断子进程是否正常终止
        child_pid = wait(&stat_val);
        printf("Child has finished :PID = %d\n",child_pid);
        if(WIFEXITED(stat_val)){
            printf("Child exited with code %d\n",WEXITSTATUS(stat_val));
        }else{
            printf("Child termimated abnormally\n");
        }
        exit(exit_code);
    }
}