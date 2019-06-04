#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
    int shmid;
    int key;
    char *p;
    int pid;
    printf("create key success key=%X\n",key);
    //创建一个共享内存
    shmid = shmget(IPC_PRIVATE,128,IPC_CREAT|0777);
    if(shmid < 0 ){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);
    
    pid = fork();
    if(pid > 0){
        //父进程用来写共享内存
        //将刚才通过shmget声明的内核共享内存映射到用户空间的地址上去
        p = (char *)shmat(shmid,NULL,0);
        if(p == NULL){
            printf("shmat function failure\n");
            return -3;
        }
    }else(pid == 0){
        //子进程用来读共享内存
    }

    
    //对映射到用户空间的共享内存进行读写
    fgets(p,128,stdin);

    //写完之后，可以开始读共享内存中的东西了
    printf("share memory data:%s",p);

    //将共享内存映射到用户空间里面的数据删除
    shmdt(p);
    //将内核中的共享内存空间删除
    shmctl(shmid,IPC_RMID,NULL);
    //这时候就无法对他进行读写操作了
    //system('ipcrm -m $shmid');
    return 0;
}