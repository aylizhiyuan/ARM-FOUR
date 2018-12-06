#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <curses.h>
int main(){
    const char witch_one[] = " First Witch  ";
    const char witch_two[] = " Second Witch ";
    const char *scan_ptr;
    //初始化屏幕
    initscr();
    //最初要显示的3组文本，它们会以1秒为间隔依次
    //显示在屏幕上，请注意对文本属性标志的开关
    move(5,15);
    //每个字符都可以有一些属性用于控制该字符在屏幕上的显示方式
    //这个是让字体加粗应该是
    attron(A_BOLD);
    //当前坐标下显示格式化的文本
    printw("%s","Macbeth");
    //关闭字体加粗的特效
    attroff(A_BOLD);
    //刷新屏幕
    refresh();
    sleep(1);


    //将光标移动到指定的位置上
    move(8,15);
    //将字体设置成
    attron(A_STANDOUT);
    printw("%s","Thunder and Lightning");
    attroff(A_STANDOUT);
    refresh();
    sleep(1);


    move(10,10);
    printw("%s","when shall we three meet again");
    move(11,23);
    printw("%s","In thunder,lightning,or in rain ?");
    move(13,10);
    printw("%s","When the hurlyburly's  done");
    move(14,23);
    printf("%s","When the battle's lost and won.");
    refresh();
    sleep(1);

    //确认演员并将它们的名字以一次一个字符的方式
    //插入到指定的位置
    attron(A_DIM);
    scan_ptr = witch_one + strlen(witch_one) - 1;
    while(scan_ptr != witch_one){
        move(10,10);
        //插入一个字符，将已有的字符右移
        insch(*scan_ptr--);
    }
    scan_ptr = witch_two + strlen(witch_two) - 1;
    while(scan_ptr != witch_two){
        move(13,10);
        insch(*scan_ptr--);
    }
    attroff(A_DIM);
    refresh();
    sleep(1);

    //最后将光标移动到屏幕的右下角，然后结束程序
    move(LINES - 1,COLS - 1);
    refresh();
    sleep(1);

    endwin();
    exit(EXIT_SUCCESS);
}
