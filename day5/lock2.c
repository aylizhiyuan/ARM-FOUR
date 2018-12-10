#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

//定义常量
const char *lock_file = "/tmp/LCK.test2";
int main(){
    int file_desc;
    int tries  = 10;
    while(tries--){
        file_desc = open(lock_file,O_RDWR | O_CREAT | O_EXCL,0444);
        if(file_desc == -1){
            //这个文件未打开
            printf("%d - Lock already persent\n",getpid());
            sleep(3);
        }else{
            //如果这个文件打开成功后，关闭文件，并删除临时文件
            printf("%d - I hava exclusive access\n",getpid());
            sleep(1);
            (void)close(file_desc);
            (void)unlink(lock_file);
            sleep(2);
        }
    }
    exit(EXIT_SUCCESS);
}
//如果这个程序单独运行的话，逻辑是这样的：第一次，通过open函数创建临时文件
//文件打开成功后，睡眠1秒后，关闭文件，并删除。下次进去的时候，继续重复10次

//如果是两个运行的程序的话
//第一个打开的进程会创建临时文件成功，第二个进程想访问这个文件的话，就会失败