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


    //循环读取消息队列
    while(1){
        memset(recvbuf.voltage,0,124);//清除recvbuf的缓存
        msgrcv(msgid,(void *)&recvbuf,124,100,0);
        printf("receive data from message queue:%s",recvbuf.voltage);
    }
 
    //删除消息队列
    msgctl(msgid,IPC_RMID,NULL);
    //删除完毕之后，可以查看消息队列
    system('ipcs -q');
    return 0;
}
//不同进程之间的消息通信
//消息队列是没有想要读的数据的时候，读的进程
//就处在阻塞状态，无需进行进程间的等待。。。。