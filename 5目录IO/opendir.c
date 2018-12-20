#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"
int main(){
    int ret;
    DIR *dp;
    ret = mkdir("./mydir",0777); //创建文件
    if(ret < 0){
        printf("create mydir failure\n");
        return -1;
    }
    printf("create mydir success\n");

    //打开文件目录
    dp = opendir("./mydir");
    if(dp == NULL){
        printf("open mydir failure\n");
        return -2;
    }
    printf("open mydir success\n");
    closedir(dp);
    return 0;
}