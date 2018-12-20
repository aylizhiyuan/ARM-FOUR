#include "stdio.h"
#include "sys/types.h"
#include "dirent.h"
int main(){
    int ret;
    DIR *dp;
    struct dirent *dir;
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
    //开始对文件目录进行读操作
    while(1){
        dir = readdir(dp);
        if(dir != NULL){
            printf("inode=%ld,name=%s\n",dir->d_ino,dir->d_name);
        }else{
            break;
        }
    }
    closedir(dp);
    return 0;
}