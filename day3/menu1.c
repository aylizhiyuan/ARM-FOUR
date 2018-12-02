#include <stdio.h>
#include <stdlib.h>
//创建一个数组指针指向一个包含菜单的数组
const char *menu[] = {
    "a - add new record",
    "d - delete record",
    "q - quit",
    NULL,
};
int getchoice(const char *greet,const char *choices[]);
int main(){
    int choice = 0;
    do{
        choice = getchoice("please select an action",menu);
        printf("you hava chosen:%c\n",choice);
    }while(choice != 'q');
    exit(0);
};
//显示菜单以及读取用户输入的函数
int getchoice(const char *greet,const char *choices[]){
    int chosen = 0;
    int selected;
    const  char **option;
    do{
        printf("Choice:%s\n",greet);
        option = choices;
        //这个循环的作用就是为了打印菜单
        while(*option){
            printf("%s\n",*option);
            option++;
        }
        //获取用户输入的字符
        selected = getchar();
        option = choices;
        //如果用户输入的字符是菜单中的第一个字符,chosen等于1,循环继续
        while(*option){
            if(selected == *option[0]){
                chosen = 1;
                break;
            }
            option++;
        }
        if(!chosen){
            printf("Incorrect choice,select again\n");
        }
    }while(!chosen);
    return selected;


};
