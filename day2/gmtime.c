#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int main(){
    //gmtime返回的结构
    struct tm *tm_ptr;
    //时间的毫秒数
    time_t the_time;
    //将当前时间写入the_time里面去
    (void) time(&the_time);
    //获取当前时间返回的结构
    tm_ptr = gmtime(&the_time);
    //打印当前时间的毫秒数
    printf("raw time is %ld\n",the_time);
    printf("gmtime gives:\n");
    printf("date:%02d/%02d/%02d\n",tm_ptr->tm_year,tm_ptr->tm_mon+1,tm_ptr->tm_mday);
    printf("time:%02d:%02d:%02d\n",tm_ptr->tm_hour,tm_ptr->tm_min,tm_ptr->tm_sec);
    exit(0);
}
