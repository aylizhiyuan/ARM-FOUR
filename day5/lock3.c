#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";
int main(){
    int file_desc;
    int byte_count;
    char *byte_to_write = "A"; 
    struct flock region_1;
    struct flock region_2;
    int res;

    //打开一个文件的描述符
    file_desc = open(test_file,O_RDWR | O_CREAT,0666);
    if(!file_desc){
        fprintf(stderr,"Unable to open %s for read/write\n",test_file);
        exit(EXIT_FAILURE);
    }
    //给文件添加一些数据
    for(byte_count = 0;byte_count < 100;byte_count++){
        (void)write(file_desc,byte_to_write,1);
    }
    //把文件的10-30字节设为区域1，并在其上设置共享锁
    region_1.l_type =  F_RDLCK;//共享锁
    region_1.l_whence = SEEK_SET; //从文件的开头
    region_1.l_start = 10; //从哪儿开始
    region_1.l_len = 20;//字节数
    //把文件的40-50字节设为区域2，并在其上设置独占锁
    region_2.l_type = F_WRLCK;//独占锁，或者叫写锁
    region_2.l_whence = SEEK_SET;
    region_2.l_start = 40;
    region_2.l_len = 10;
    //现在锁定文件
    printf("Process %d locking file\n",getpid());
    res = fcntl(file_desc,F_SETLK,&region_1);
    if(res == -1) fprintf(stderr,"Failed to lock region_1\n");
    res = fcntl(file_desc,F_SETLK,&region_2);
    if(res == -1) fprintf(stderr,"Failded to lock region_2\n");

    sleep(60);
    printf("Process %d closing file\n",getpid());
    close(file_desc);
    exit(EXIT_SUCCESS);
}
//程序首先创建了一个文件，并以可读可写方式打开它，然后再在文件中添加一些数据
//接着在文件中设置两个区域：第一个区域为10-30字节，使用共享锁
//第二个区域是40-50，使用独占锁，然后程序调用fcntl来锁定这两个区域
//在关闭文件和程序退出前等待1分钟