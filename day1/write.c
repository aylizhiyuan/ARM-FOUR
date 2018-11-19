#include <unistd.h>
#include <stdlib.h>
int main(){
    if((write(1,"here is some data\n",18))!=18){
        write(2,"a write error has occurred on file descriptor 1\n",46);
    }
    exit(0);
}
//系统调用write的作用是把缓冲区buf的前nbytes个字节写入与文件描述符fildes关联
//的文件中。它返回实际写入的字节数

