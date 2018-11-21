#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
int main(){
    char c;
    int in,out;
    //以只读的形式打开file.in文件
    in = open("file.in",O_RDONLY);
    //创建一个可读可写的file.out文件
    out = open("file.out",O_WRONLY|O_CREAT,S_IRUSR|S_IWUSR);
    //读取file.in文件,一个字节一个字节的读取，将内容写入file.out
    while(read(in,&c,1) == 1){
        write(out,&c,1);
    }
    exit(0);
}
