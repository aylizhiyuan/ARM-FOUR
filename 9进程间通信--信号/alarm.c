#include "stdio.h"
#include "sys/types.h"
#include "signal.h"
#include "stdlib.h"
int main(){
    int i = 0;
    printf("alarm before\n");
    alarm(9);
    printf("raise after\n");
    while(i < 20){
        i++;
        slepp(1);
        printf("process things i=%d\n",i);
    }
    return 0;
}