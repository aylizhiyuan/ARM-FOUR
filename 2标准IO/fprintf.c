#include "stdio.h"
int main(){
    FILE *fp;
    int i = 10;
    fp = fopen("./a.c","w+");
    if(fp == NULL){
        printf("open a.c failure\n");
        return -1;
    }
    fprintf(fp,"open a.c success i=%d\n",i);
    fclose(fp);
    return 0;
}