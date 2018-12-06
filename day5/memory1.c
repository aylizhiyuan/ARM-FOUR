#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define A_MEGABYTE (1024 * 1024)

int main(){
    char *some_memory;
    int megabyte = A_MEGABYTE;
    int exit_code = EXIT_FAILURE;
    some_memory = (char *)malloc(megabyte);
    if(some_memory != NULL){
        sprintf(some_memory,"hello world\n");
        printf("%s",some_memory);
        exit_code = EXIT_FAILURE;
    }
    exit(exit_code);
}
//这个程序要求malloc函数给它返回一个指向1mb内存空间的指针
//首先检查并确保malloc函数被成功调用，然后通过使用其中的
//部分内存来表明分配的内存确实已经存在。
//当运行这个程序时，你会看到程序输出hello world ，这表明
//malloc确实返回了1mb的可用内存。
