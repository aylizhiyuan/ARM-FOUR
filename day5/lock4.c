#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

const char *test_file = "/tmp/test_lock";
#define SIZE_TO_TRY 5
void show_lock_info(struct flock *to_show);

int main(){
    int file_desc;
    int res;
    struct flock region_to_test;
    int start_byte;
    //打开一个文件描述符
    file_desc = open(test_file,O_RDWR | O_CREAT,0666);
    if(!file_desc){
        fprintf(stderr,"Unable to open %s for read/write",test_file);
        exit(EXIT_FAILURE);
    }
    //设置希望测试的文件的区域
    for(start_byte = 0;start_byte < 99;start_byte += SIZE_TO_TRY){
        //这个应该是循环20次
        region_to_test.l_type = F_WRLCK;//独占锁
        region_to_test.l_whence = SEEK_SET; //从文件的开头处开始
        region_to_test.l_start = start_byte;//0-5-10-15.....
        region_to_test.l_len = SIZE_TO_TRY; 
        //第一次测试0到5，第二次测试5-10,第三次测试10-15
        region_to_test.l_pid = -1;
        printf("Testing F_WRLCK on region from %d to %d\n",start_byte,start_byte + SIZE_TO_TRY);
        //现在测试文件上的锁
        res = fcntl(file_desc,F_GETLK,&region_to_test);
        if(res == -1){
            fprintf(stderr,"F_GETLK failed\n");
        }
        if(region_to_test.l_pid != -1){
            //这个判断搞不明白
            printf("Lock would fail.F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        }else{
            printf("F_WRLCK - Lock would success\n");
        }
        //用共享锁重复测试一遍，再次设置希望测试的文件区域
        region_to_test.l_type = F_RDLCK;
        region_to_test.l_whence = SEEK_SET;
        region_to_test.l_start = start_byte;
        region_to_test.l_len = SIZE_TO_TRY;
        region_to_test.l_pid = -1;
        printf("Testing F_RDLCK on region from %d to %d\n",start_byte,start_byte + SIZE_TO_TRY);
        //再次测试文件上的锁
        res = fcntl(file_desc,F_GETLK,&region_to_test);
        if(res == -1){
            fprintf(stderr,"F_GETLK failed\n");
            exit(EXIT_FAILURE);
        }
        if(region_to_test.l_pid != -1){
            printf("Lock would fail.F_GETLK returned:\n");
            show_lock_info(&region_to_test);
        }else{
            printf("F_RDLCK - Lock would successed\n");
        }
    }
    close(file_desc);
    exit(EXIT_SUCCESS);
}
void show_lock_info (struct flock *to_show){
    printf("\tl_type %d, ", to_show->l_type);
    printf("l_whence %d, ",to_show->l_whence);
    printf("l_start %d, ",(int)to_show->l_start);
    printf("l_len %d, ",(int)to_show->l_len);
    printf("l_pid %d\n",to_show->l_pid);

}