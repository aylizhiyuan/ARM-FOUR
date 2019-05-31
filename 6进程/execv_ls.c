#include <stdio.h>
#include <unistd.h>
int main(void){
    pid_t pid;
    pid = fork();
    if(pid == -1){
        perror("fork error");
        exit(1);
    }else if(pid > 0){
        sleep(1);
        printf("parent\n");
    }else{
        char *argv[] = {"ls","-l",NULL};
        execv("/bin/ls",argv);
    }
    return 0;
}