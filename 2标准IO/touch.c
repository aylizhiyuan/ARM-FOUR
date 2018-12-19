#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *fp;
    fp = fopen(argv[1],"w+");//创建可读写文件
    if(fp == NULL){
        printf("create file %s failure\n",argv[1]);
        return -1;
    }
    printf("create file %s success\n",argv[1]);
    fclose(fp);
    return 0;
}