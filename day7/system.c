#include <stdlib.h>
#include <stdio.h>
int main(){
    printf("Running ps with system\n");
    system("ps ax");
    printf("Done.\n");
    exit(0);
}
//例子中以字符串 ps ax 为参数调用system函数
//从而在程序中执行ps命令。