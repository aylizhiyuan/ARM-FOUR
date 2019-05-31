#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int argc,char *argv[]){
    int n = 5,i;
    pid_t p,q;
    pid_t wpid;
    if(argc == 2){
        n = atoi(argv[1]);
    }
    for(i=0;i<n;i++){
        p = fork();
        if(p == 0){
            break;
        }else if(i == 3){
            p = q; //保存第三个子进程的ID号
        }
    }
    if(n == i){
        sleep(n);
        printf("i am parent,pid = %d\n",getpid());
        //waitpid(q,NULL,0);//指定某个进程回收,0表示阻塞
        //while(waitpid(-1,NULL,0)); //回收所有的子进程
        do {
            wpid = waitpid(-1,NULL,WNOHANG);//非阻塞的模式
            //if wpid == 0 说明子进程正在运行
            if(wpid > 0){
                n --;
            }
            sleep(1);
        }while(n > 0);
        printf("wait finish\n");
    }else{
        sleep(i);
        printf("i am %dth child,pid = %d\n,gpid=%d\n",i+1,getpid(),getgid());
        while(1);
    }
    return 0;
}