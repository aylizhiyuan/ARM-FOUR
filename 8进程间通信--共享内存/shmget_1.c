#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
    int shmid;
    int key;
    //创建的共享内存的key值就不一样了
    //传递的参数不一样，那么创建的共享内存的key值就不一样
    //类似于无名管道和有名管道的区别吧！
    //有名管道可以实现无亲缘关系的进程通信
    //通过这种方式创建Key值也是可以实现无亲缘关系的共享
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
    //system('ipcrm -m $shmid');
    return 0;
}