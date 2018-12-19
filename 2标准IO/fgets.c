#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *fp;
    char buf[] = "hello liunx\n";
    char readbuf[128] = {0};
    fp = fopen("./a.c","w+");//打开a.c文件
    if(fp == NULL){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success\n");
    //写数据
    fputs(buf,fp);
    //回到文件指针的初始位置
    fseek(fp,0,SEEK_SET);
    //读数据
    fgets(readbuf,128,fp);
    printf("readbuf:%s\n",readbuf);
    fclose(fp);
    return 0;
}