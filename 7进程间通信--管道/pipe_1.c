#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
int main(){
    int fd[2];
    int ret;
    //创建一个管道，会返回两个文件描述符 fd[0] fd[1]
    ret = pipe(fd);
    if(ret < 0){
        printf("create pipe failure\n");
        return -1;
    }
    printf("create pipe success fd[0]=%d,fd[1]=%d\n",fd[0],fd[1]);
    return 0;
}