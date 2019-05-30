#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "stdlib.h"
#include "fcntl.h"
int main(){
    int i;
    int fd;
    int process_inter = 0;
    fd = open("./myfifo",O_RDONLY);
    if(fd < 0){
        printf("open myfifo faiulre\n");
        return -1;
    }
    printf("open myfifo success\n");
    //第二个进程从有名管道中读取数据
    //如果数据
    read(fd,&process_inter,1);
    while(process_inter == 0);
    for(i=0;i<5;i++){
        printf("this is first process i=%d\n",i);
        usleep(100);
    }
    while(1);
    return 0;
}