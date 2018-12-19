#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include "string.h"
int main(int argc,char *argv[]){
    FILE *src_fp;
    int read_ret;
    if(argc < 2){
        printf("please input src file\n");
        return -1;
    }
    src_fp = fopen(argv[1],"r");
    if(src_fp == NULL){
        printf("open src file %s failure\n",argv[1]);
        return -2;
    }
    printf("open src file %s success\n",argv[1]);
    //开始读写
    while(1){
        read_ret = fgetc(src_fp);
        if(feof(src_fp)){
            printf("read file %s end\n",argv[1]);
            break;
        }
        fputc(read_ret,stdout);
    }
    fclose(src_fp);
    return 0;
}