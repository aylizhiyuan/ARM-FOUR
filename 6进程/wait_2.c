#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(void){
    pid_t pid,wpid;
    int status;
    pid = fork();
    if(pid == 0){
        printf("---child,my parent = %d,going to sleep 10s\n",getppid());
        sleep(20);
        printf("--------child die--------\n");
        exit(76);
    }else if(pid > 0){
        wpid = wait(&status);
        if(wpid == -1){
            perror("wait error");
            exit(1);
        }
        if(WIFEXITED(status)){
            printf("child exit with %d\n",WEXITSTATUS(status));
        }
        //如果子进程是异常退出的话
        if(WIFSIGNALED(status)){
            printf("child killed by %d\n",WTERMSIG(status));
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