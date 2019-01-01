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
    struct msgbuf sendbuf,recvbuf;
    msgid = msgget(IPC_PRIVATE,0777);
    if(msgid < 0){
        printf("create message queue failure\n");
        return -1;
    }
    printf("create message queue success msgid=%d\n",msgid);
    system('ipcs -q');//查看的是消息队列

    sendbuf.type = 100;
    printf("please input message:\n");
    fgets(sendbuf.voltage,124,stdin);

    //往消息队列里面写
    msgsnd(msgid,(void *)&sendbuf,strlen(sendbuf.voltage),0);


    //读取消息队列里面的数据
    //读之间，先清除缓存
    memset(recvbuf.voltage,0,124);
    readret = msgrcv(msgid,(void *)&recvbuf,124,100,0);
    //真正读到的字节数
    printf("recv:%s\n",recvbuf.voltage);
    printf("readret=%d\n",readret);

    //第二次去读
    msgrcv(msgid,(void *)&recvbuf,124,100,0);
    printf("second read after\n");
    //消息队列读完之后，消息队列就被删除了

    //删除消息队列
    msgctl(msgid,IPC_RMID,NULL);
    //删除完毕之后，可以查看消息队列
    system('ipcs -q');
    return 0;
}