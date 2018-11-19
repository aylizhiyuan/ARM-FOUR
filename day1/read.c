#include <unistd.h>
#include <stdlib.h>
int main(){
    char buffer[128];
    int nread;
    nread = read(0,buffer,128);//从标准输入中读取128个字节的数据
    if(nread == -1)
        write(2,"a read error has occurred\n",26);
    if((write(1,buffer,nread))!=nread)
        write(2,"a write error has occurred\n",27);

    exit(0);
}
//这个程序会把标准输入的前128个字节复制到标准输出。如果输入少于128个字节，就把他们全部复制过去
