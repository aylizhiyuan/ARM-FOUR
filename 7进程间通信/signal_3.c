#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdio.h"
#include "stdlib.h"
#include "unistd.h"
void myfun(int signum){
    int i;
    i=0;
    while(1<5){
        printf("receive signum=%d\n",signum);
    }
    return;
}
int main(){
    pid_t pid;
    pid =fork();
    if(pid > 0){
       //父进程
       int i;
       signal(10,myfun);
       i=0;
       while(1){
           printf("parent process things,i=%d\n",i);
           sleep(1);
           i++;
       }
    }
    if(pid == 0){
      //子进程
      sleep(10);
      kill(getppid(),10);
      sleep(10);
      exit(0);
    }
    return 0;
}