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

    key = ftok("./a.c",'a');
    if(key < 0){
        printf("create key fialure\n");
        return -2;
    }
    printf("create key success key=%X\n",key);
    //创建一个共享内存
    shmid = shmget(key,128,IPC_CREAT|0777);
    if(shmid < 0 ){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);
    system('ipcs -m');

    //将刚才通过shmget声明的内核共享内存映射到用户空间的地址上去
    p = (char *)shmat(shmid,NULL,0);
    if(p == NULL){
        printf("shmat function failure\n");
        return -3;
    }
    //对映射到用户空间的共享内存进行读写
    fgets(p,128,stdin);

    //写完之后，可以开始读共享内存中的东西了
    printf("share memory data:%s",p);


    //system('ipcrm -m $shmid');
    return 0;
}