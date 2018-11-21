#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
//其中argc是参数的个数（包括程序名称本身）
//argv[]数组包含了所有的参数
int main(int argc,char *argv[]){
    int opt;
    //getopt返回下一个选项字符
    while((opt = getopt(argc,argv,":if:lr")) != -1){
        switch(opt){
            case 'i':
            case 'l':
            case 'r':
                printf("option:%c\n",opt);
                break;
            case 'f':
                printf("filename:%s\n",optarg);//打印文件的名称
                break;
            case ':':
                //如果将选项字符串的第一个字符设置为冒号，则返回:
                printf("option needs a value\n");
                break;
            case '?':
                printf("unknown option:%c\n",optopt);//不能识别的参数
                break;
        }
    }
    //optind被设置成下一个待处理参数的索引
    for(;optind < argc;optind++)
        printf("argument:%s\n",argv[optind]);
    exit(0);
}
