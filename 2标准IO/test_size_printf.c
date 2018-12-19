#include "stdio.h"
#include "unistd.h"
int main(){
    char buf[] = "hello liunx";
    int i = 1;
    while(i <= 95){
        printf("%s",buf);
        i++;
    }
    while(1);
    return 0;
}