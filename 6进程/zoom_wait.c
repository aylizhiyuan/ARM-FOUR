#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t pid,wpid;
    pid = fork();
    if(pid == 0){
        printf("---child,my parent = %d,going to sleep 10s\n",getppid());
        sleep(10);
        printf("--------child die--------\n");
    }else if(pid > 0){
        wpid = wait(NULL);//回收子进程，不关心退出状态
        if(wpid == -1){
            perror("wait error");
        }
        while(1){
            printf("i am parent pid = %d,myson = %d\n",getpid(),pid);
            sleep(1);
        }
    }else{
        perror("fork");
        return 1;
    }
    return 0;
}