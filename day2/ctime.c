#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main()
{
    //time_t类型是一个返回日期相关的结构体数据
    time_t timeval;
    //将当前时间的信息输入到这个结构体里面
    (void)time(&timeval);
    printf("the data is :%s",ctime(&timeval));
    exit(0);
}
