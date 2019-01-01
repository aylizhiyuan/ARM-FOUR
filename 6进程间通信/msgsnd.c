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
    struct msgbuf sendbuf;
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

    //删除消息队列
    msgctl(msgid,IPC_RMID,NULL);
    //删除完毕之后，可以查看消息队列
    system('ipcs -q');
    return 0;
}