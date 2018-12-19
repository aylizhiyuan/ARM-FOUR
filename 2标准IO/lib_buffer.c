#include "stdio.h"
#include "unistd.h"
int main(){
    char buf[] = "hello liunx";//user buffer
    
    //是因为缓存并未写入内核缓存中去，是直接放在库缓存中的
    //printf遇到\n的时候或者是库函数写满的时候，才会直接写入库函数中去
    printf("%s",buf);
    //write(1,buf,sizeof(buf));
    while(1);
    return 0;
}