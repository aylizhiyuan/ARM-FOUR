#include <stdlib.h>
#include <stdio.h>
#define ONE_K (1024)

int main(){
    char *some_memeory;
    int exit_code = EXIT_FAILURE;
    //声明一段内存，大概是1KB
    some_memeory = (char *)malloc(ONE_K);
    if(some_memeory != NULL){
        free(some_memeory);
        printf("Memory allocated and freed again\n");
        exit_code = EXIT_FAILURE;
    }
    exit(exit_code);
}
//一旦调用free释放了一块内存，它就不再属于这个进程了
