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
       printf("I am parent pid = %d,parentID = %d\n",getpid(),getppid());
   }else if(pid == 0){
       printf("child pid = %d ,parentID = %d\n",getpid(),getppid());
       sleep(3);
       printf("child pid = %d ,parentID = %d\n",getpid(),getppid());
   }
   return 0;
}