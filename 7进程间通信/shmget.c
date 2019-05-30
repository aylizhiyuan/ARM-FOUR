#include "sys/types.h"
#include "sys/shm.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
int main(){
    int shmid;
    //创建一个共享内存
    shmid = shmget(IPC_PRIVATE,128,0777);
    if(shmid < 0 ){
        printf("create share memory failure\n");
        return -1;
    }
    printf("create share memory success shmid=%d\n",shmid);
    system('ipcs -m');
    system('ipcrm -m $shmid');
    return 0;
}