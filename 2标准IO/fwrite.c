#include "stdio.h"
int main(int argc,char *argv[]){
    FILE *fp;
    char buf[] = "hello liunx";
    char readbuf[128] = {0};
    fp = fopen("./a.c","w+");
    if(fp == NULL){
        printf("open file a.c failure\n");
        return -1;
    }
    printf("open file a.c success\n");
    fwrite(buf,sizeof(char),sizeof(buf),fp);
    //调整文件位置指针
    rewind(fp);
    fread(readbuf,sizeof(char),sizeof(readbuf),fp);
    printf("readbuf:%s\n",readbuf);
    fclose(fp);
    return 0;
}