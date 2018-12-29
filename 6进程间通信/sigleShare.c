#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
void myfun(int signum){
    return;
}
int main(){
    int shmid;
    int key;
    char *p;
    int pid;
    printf("create key success key=%d\n",key);
    shmid = shmget(IPC_PRIVATE,128,0777);
    if(shmid < 0){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);

    //创建父子进程
    pid = fork();
    if(pid > 0){
        signal(SIGUSR2,myfun);
        p = (char *)shmat(shmid,NULL,0);
        if(p == NULL){
            printf("shmat function failure\n");
            return -3;
        }
        while(1){
            //对映射到用户空间的共享内存进行读写
            printf("parent process start write share memory\n");
            fgets(p,128,stdin);
            kill(pid,SIGUSR1);//让父进程发送一个信号给子进程
            //通知子进程去读共享内存的数据
            pause();//等待子进程读 
        }
    }
    if(pid == 0){
        signal(SIGUSR2,myfun);
        p = (char *)shmat(shmid,NULL,0);
        if(p == NULL){
            printf("child process shmat function failure\n");
        }
        while(1){
            pause();//等待父进程唤醒
            //写完之后，可以开始读共享内存中的东西了
            printf("share memory data:%s",p);
            kill(getppid(),SIGUSR2);
        }//子进程
    }
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    system('ipcs -m');
    return 0;
}