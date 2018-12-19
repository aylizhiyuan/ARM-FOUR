#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc,char *argv[]){
    int fd;
    //追加方式打开
    fd = open("./a.c",O_APPEND | O_RDWR,0777);
    if(fd < 0){
        printf("create file a.c failure\n");
        return -1;
    }
    printf("create file a.c success,fd=%d\n",fd);
    close(fd);
    return 0;
}