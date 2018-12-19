#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *fp;
    int ret;
    fp = fopen("./a.c","w+");
    if(fp == NULL){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success\n");
    fputc('a',fp);
    //设置文件读写指针
    rewind(fp);
    //开始读
    ret = fgetc(fp);
    printf("ret=%c\n",ret);
    fclose(fp);
    return 0;
}