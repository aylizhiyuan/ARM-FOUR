#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <errno.h>

int main(){
    int file_desc;
    int save_errno;
    //如果文件不存在则创建它，如果存在的话，就直接打开它
    file_desc = open("/tmp/LCK.test",O_RDWR|O_CREAT|O_EXCL,0444);
    if(file_desc == -1){
        //打开失败的情况
        save_errno = errno;
        printf("Open failed with errno %d\n",save_errno);
    }else{
        //打开成功了
        printf("Open successed\n");
    }
    exit(EXIT_SUCCESS);
}
//许多应用程序只需要能够针对某个资源创建一个锁文件即可。然后其他程序就可以通过检查
//这个文件来判断他们自己是否被允许访问这个资源。
