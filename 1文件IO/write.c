#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc,char *argv[]){
    int fd;
    char buf[] = "hello liunx";
    int wr_ret;
    fd = open("./a.c",O_RDWR | O_TRUNC);
    if(fd < 0){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success,fd=%d\n",fd);
    wr_ret = write(fd,buf,sizeof(buf));
    printf("wr_ret=%d\n",wr_ret);
    close(fd);
    return 0;
}