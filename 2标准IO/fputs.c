#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *fp;
    char buf[] = "hello liunx\n";
    fp = fopen("./a.c","w+");//打开a.c文件
    if(fp == NULL){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success\n");
    //写数据
    fputs(buf,fp);
    fclose(fp);
    return 0;
}