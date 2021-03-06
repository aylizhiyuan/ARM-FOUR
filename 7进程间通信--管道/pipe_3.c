#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
int main(){
    int fd[2];
    int ret;
    char writebuf[] = "hello liunx";
    char readbuf[128] = {0};
    //创建一个管道，会返回两个文件描述符 fd[0] fd[1]
    ret = pipe(fd);
    if(ret < 0){
        printf("create pipe failure\n");
        return -1;
    }
    printf("create pipe success fd[0]=%d,fd[1]=%d\n",fd[0],fd[1]);
    //先使用write函数将字符串内容写入管道中去
    write(fd[1],writebuf,sizeof(writebuf));
    //再使用read函数将管道内的字符串写入到readbuf中去
    read(fd[0],readbuf,128);
    printf("readbuf=%s\n",readbuf);
    //写完之后，关闭这两个文件描述符

    //第二次读管道内的东西
    //管道因为读完后自动清空了，管道内的内容已经没有了，就会造成读阻塞
    memset(readbuf,0,128);
    read(fd[0],readbuf,128);
    printf("second read after\n");
    close(fd[0]);
    close(fd[1]);
    return 0;
}