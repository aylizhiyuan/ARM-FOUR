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

    signal(SIGUSR2,myfun);
    p = (struct mybuf *)shmat(shmid,NULL,0);
    if(p == NULL){
        printf("shmat function failure\n");
        return -3;
    }

    //获得客户端的pid


    p->pid = getpid(); //把服务端的pid写入共享内存
    pause(); //等待客户端去读服务端的pid

    pid = p->pid;//这时候是读取客户端的pid

    while(1){
         //对映射到用户空间的共享内存进行读写
        printf("parent process start write share memory\n");
        fgets(p->buf,128,stdin);
        kill(pid,SIGUSR1);//给客户端发送一个信号，告诉他我们已经写完了
        //通知客户端去读共享内存的数据
        pause();//等待客户端读 
    }
    shmdt(p);
    shmctl(shmid,IPC_RMID,NULL);
    system('ipcs -m');
    return 0;
}