#include <unistd.h>
#include <stdlib.h>
int main(){
    //写入文件
    if((write(1,"here is some data\n",18))!=18){
        write(2,"a write error has occurend on file descriptor 1\n",46);
    }
    exit(0);
}
