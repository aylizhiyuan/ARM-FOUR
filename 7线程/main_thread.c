#include "stdio.h"
#include "pthread.h"
#include "stdlib.h"
#include "string.h"
#include "sys/types.h"
#include "unistd.h"
struct student {
    int age;
    char name[20];
};
void *thrread_fun(void *stu){
    printf("student age is %d,name is %s\n",((struct student *)stu)->age,((struct student *)stu)->name);
    return (void *)0;
};
int main(){

}