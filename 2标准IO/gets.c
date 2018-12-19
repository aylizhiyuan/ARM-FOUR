#include "stdio.h"
int main(){
    char buf[128] = {0};
    fgets(buf,128,stdin);
    //gets(buf);//hava \n
    //fputs(buf,stdout);
    puts(buf);
    return 0;
}