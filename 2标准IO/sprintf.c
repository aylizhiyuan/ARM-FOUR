#include "stdio.h"
int main(){
    int i = 10;
    char buf[128] = {0};
    sprintf(buf,"i=%d",i);
    return 0;
}