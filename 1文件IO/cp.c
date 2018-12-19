#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
int main(int argc,char *argv[]){
    int rd_fd,wr_fd;
    char read_buf[128] = {0};
    int rd_ret = 0;
    if(argc < 3){
        printf("please intput src file and des file\n");
        return -1;
    }
    //打开第一个要拷贝的文件
    rd_fd = open(argv[1],O_RDONLY);
    if(rd_fd < 0){
        printf("open src file %s failure\n",argv[1]);
        return -2;
    }
    printf("open src file %s success,rd_fd=%d\n",argv[1],rd_fd);
    wr_fd = open(argv[2],O_WRONLY);
    if(wr_fd < 0){
        printf("open des file %s failure\n",argv[2]);
        return -3;
    }
    printf("open des file %s success wr_fd=%d\n",argv[2],wr_fd);
    //进程在开启的时候，默认打开的文件描述符是012
    //那么当你打开第一个文件的时候，它的文件描述符应该是3

    while(1){
         //先读
        rd_ret = read(rd_fd,read_buf,128);
        if(rd_ret < 128) break;
        //后写
        write(wr_fd,read_buf,rd_ret);
        memset(read_buf,0,128);
    }
    write(wr_fd,read_buf,rd_ret);
    close(rd_fd);
    close(wr_fd);
    return 0;
}