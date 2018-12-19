#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
int main(int argc,char *argv[]){
    int fd;
    char buf[] = "hello liunx";
    int wr_ret,rd_ret;
    char read_buf[128] = {0};
    fd = open("./a.c",O_RDWR | O_TRUNC);
    if(fd < 0){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success,fd=%d\n",fd);
    wr_ret = write(fd,buf,sizeof(buf));
    printf("wr_ret=%d\n",wr_ret);

    //通过lseek,将文件的指针设定在开头的位置
    lseek(fd,0,SEEK_SET);
    //开始读
    //读取的时候会出现问题，这个问题主要是读的内容为空
    //因为写的时候，文件的指针指向末尾，读的时候它会从当前的
    //指针位置开始读
    rd_ret = read(fd,read_buf,128);
    printf("recv data:read_buf=%s\n",read_buf);
    close(fd);
    return 0;
}