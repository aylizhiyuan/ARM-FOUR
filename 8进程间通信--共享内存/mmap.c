#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>
int main(void){
    int len,ret; 
    char *p = NULL;
    int fd = open("mytest.txt",O_CREAT|O_RDWR,0644);
    if(fd < 0){
        perror("open error:");
        exit(1);
    }
    len = ftruncate(fd,4);
    if(len == -1){
        perror("ftruncate error:");
        exit(1);
    }
    //在该进程中创建了一个映射区，这个映射区对应的就是磁盘上的mytest.txt
    //我们可以直接可以对这个文件进行读写了,不用经过内核
    p = mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_SHARED,fd,0);
    if(p == MAP_FAILED){
        perror("mmap error:");
        exit(1);
    }
    strcpy(p,"abc");//写数据
    ret = munmap(p,4);//将映射区关闭
    close(fd);//关闭文件
    return 0;

}