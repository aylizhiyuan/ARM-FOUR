#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"
int main(){
    int ret;
    ret = mkdir("./mydir",0777); //创建文件
    if(ret < 0){
        printf("create mydir failure\n");
        return -1;
    }
    printf("create mydir success\n");
    return 0;
}