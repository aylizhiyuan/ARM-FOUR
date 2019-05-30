#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
struct mybuf {
    int pid;
    char buf[124];
};
void myfun(int signum){
    return;
}
int main(){
    int shmid;
    int key;
    struct mybuf *p;
    int pid;
    key = ftok("./a.c",'a');
    if(key < 0){
        printf('creat key failure\n');
        return -1;
    }
    printf("create key success key=%d\n",key);

    shmid = shmget(key,128,IPC_CREAT | 0777);
    if(shmid < 0){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);

    signal(SIGUSR1,myfun);
    p = (struct mybuf *)shmat(shmid,NULL,0);
    if(p == NULL){
        printf("shmat function failure\n");
        return -3;
    }
    //读取共享内存中父进程的pid
    pid = p->pid;
    //将客户端的pid写入共享内存中
    p->pid = getpid();
    //通知父进程，发送信号
    kill(pid,SIGUSR2);

    //客户端是读数据
    while(1){
        pause();//等待服务器端写完数据
        printf("client process receve data from share memory:%s",p->buf);
        kill(pid,SIGUSR2); //服务器端可以写共享内存了
    }
    //这个地方需要将共享内存的数据也给清除掉吗？
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    system('ipcs -m');
    return 0;
}