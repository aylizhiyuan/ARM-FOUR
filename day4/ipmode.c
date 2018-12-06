#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
#include <string.h>
#define PW_LEN 256
#define NAME_LEN 256

int main(){
    char name[NAME_LEN];
    char password[PW_LEN];
    const char *real_password = "xyzzy";
    int i = 0;
    initscr();
    move(5,10);
    printw("%s","Please login:");
    move(7,10);
    printw("%s","User name:");
    getstr(name);//获取键盘输入的用户名
    move(8,10);
    printw("%s","Passwrod:");
    refresh();
    //用户输入密码的时候，你不能让密码回显在屏幕上
    //检查用户的密码是否等于xyzzy
    cbreak();
    noecho();
    memset(password,'\0',sizeof(password));
    while(i<PW_LEN){
        password[i] = getch();
        if(password[i] == '\n') break;
        move(8,20 + i);
        addch('*');
        refresh();
        i++;
    }
    //最后，重启键盘回显，并给出密码成功或者失败的信息
    echo();
    nocbreak();
    move(11,10);
    if(strncmp(real_password,password,strlen(real_password)) == 0){
        printw("%s","Correct");
    }else{
        printw("%s","Wrong");
    }
    printw("%s",password);
    refresh();
    sleep(2);

    endwin();
    exit(EXIT_SUCCESS);
}
