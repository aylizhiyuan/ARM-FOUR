#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/wait.h>

int var = 100;
int main(void){
    int *p;
    pid_t pid;
    int fd;
    fd = open("temp",O_RDWR|O_CREAT|O_TRUNC,0644);
    if(fd < 0){
        perror("open error");
        exit(1);
    }
    unlink("temp");//删除临时文件目录项
    ftruncate(fd,4);
    p = (int *)mmap(NULL,4,PROT_READ|PROT_WRITE,MAP_PRIVATE,fd,0);
    if(p == MAP_FAILED){
        perror("mmap error");
        exit(1);
    }
    close(fd);//映射区建立完毕，即可关闭文件

    pid = fork();
    if(pid == 0){
        //子进程
        *p = 2000;
        var = 1000;
        printf("child,*p=%d,var=%d\n",*p,var);
    }else{
        //父进程
        sleep(1);
        printf("parent,*p=%d,var=%d\n",*p,var);
        wait(NULL);
        int ret = munmap(p,4);
        if(ret == -1){
            perror("munmap error");
            exit(1);
        }
    }

}
//结论：父子进程共享的是什么？0-3G的虚拟内存空间是不共享的
//共享的是打开的文件 2. mmap建立的映射区
