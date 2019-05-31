#include <stdio.h>
#include <unistd.h>
int main(void){
    pid_t pid;
    printf("xxxxxxxxxx\n");
    pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }else if(pid == 0){
        printf("I am child ,pid=%u,ppid=%lu\n",getpid(),getppid());
    }else{
        printf("I am parent ,pid=%u,ppid=%lu\n",getpid(),getppid());
    }
    return 0;
}