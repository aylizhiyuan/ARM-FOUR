#include "sys/types.h"
#include "sys/msg.h"
#include "signal.h"
#include "unistd.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
struct msgbuf {
    long type;
    char voltage[124];
    char ID[4];
};
int main(){
    int msgid;
    int readret;
    int key;
    struct msgbuf sendbuf,recvbuf;
    //创建一个独立的key值供两个进程之间进行通信
    key = ftok("./a.c",'a');
    if(key < 0){
        printf("create key failure\n");
        return -2;
    }
    msgid = msgget(key,IPC_CREAT | 0777);
    if(msgid < 0){
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue success msgid=%d\n",msgid);
    system('ipcs -q');//查看的是消息队列


    sendbuf.type = 100;
    while(1){
        memset(sendbuf.voltage,0,124);//清除sendbuf的缓存
        printf("please input message:\n");
        fgets(sendbuf.voltage,124,stdin);
        //往消息队列里面写
        msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);
    }
 
    //删除消息队列
    msgctl(msgid,IPC_RMID,NULL);
    //删除完毕之后，可以查看消息队列
    system('ipcs -q');
    return 0;
}
//不同进程之间的消息通信