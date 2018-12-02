#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
const char *menu[] = {
    "a - add new record",
    "d - delete record",
    "q - quit",
    NULL,
};
int getchoice(const char *greet,const char *choices[]);
int main(){
    int choice = 0;
    //用isatty函数来测试标准输出是否已经连接到一个终端，如果没有
    //则推出程序。
    if(!isatty(fileno(stdout))){
        fprintf(stderr,"You are not a terminal!\n");
        exit(1);
    }
    do{
        choice = getchoice("Please select an action",menu);
        printf("You hava chosen:%c\n",choice);
    }while(choice != 'q');
    exit(0);
}
int getchoice(const char *greet,const char *choices[]){
    int chosen = 0;
    int selected;
    const char **option;
    do{
        printf("Choice:%s\n",greet);
        option = choices;
        while(*option){
            printf("%s\n",*option);
            option++;
        }
        //解决回车的问题
        do{
            selected = getchar();
        }while(selected == '\n');
        option = choices;
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
}
