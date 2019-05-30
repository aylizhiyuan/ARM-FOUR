#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
#include "string.h"
int main(){
    int fd[2];
    int ret;
    int i = 0;
    char writebuf[] = "hello liunx";
    char readbuf[128] = {0};
    //创建一个管道，会返回两个文件描述符 fd[0] fd[1]
    ret = pipe(fd);
    if(ret < 0){
        printf("create pipe failure\n");
        return -1;
    }
    printf("create pipe success fd[0]=%d,fd[1]=%d\n",fd[0],fd[1]);
    //循环去往这个管道去写内容，看看会不会写阻塞
    while(i < 5457){
        write(fd[1],writebuf,sizeof(writebuf));
    }
    printf("write pipe end\n");
    close(fd[0]);
    close(fd[1]);
    return 0;
}