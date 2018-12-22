#include "stdio.h"
#include "unistd.h"
#include "stdlib.h"
int main(){
    int ret;
    //创建一个有名管道myfifo文件
    //它的文件类型是p,它是不占据磁盘空间的
    ret = mkfifo("./myfifo",0777);
    if(ret < 0){
        printf("create myfifo failure\n");
        return -1;
    }
    printf("create myfifo success\n");
    return 0;
}