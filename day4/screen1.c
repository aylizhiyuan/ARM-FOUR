#include <unistd.h>
#include <stdlib.h>
#include <curses.h>
int main(){
    //所有的curses程序都必须在开始使用之前进行初始化
    initscr();

    //增加将光标移动到逻辑屏幕坐标5, 15处
    //输出hello world然后刷新无力屏幕的代码
    //最后调用函数将程序暂停两秒看结果

    move(5,15);
    printw("%s","hello world");
    refresh();
    sleep(2);

    //并在结束使用后允许curses恢复原先的设置
    endwin();
    exit(EXIT_SUCCESS);
}
//最后编译的时候，使用gcc screen1.c -o screen1 -lcurses
//来编译程序，指明所需要的静态库文件的名称
