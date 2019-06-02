# Liunx系统编程--APUE

## 1. 进程的概念

程序，是指编译好的二进制文件，在磁盘你上，不占用系统资源(cpu、内存、打开的文件个数、设备、锁)

进程是一个抽象的概念，与操作系统原理联系紧密。进程是活跃的程序，占用系统资源，在内存中执行，程序运行起来，占用一个进程


并发指的是在操作系统中，一个时间段中有多个进程都处于已启动运行到运行完毕之间的状态，但，任意时刻只有一个进程在执行

进程的基本状态有五种，分别为初始态、就绪态、运行态、挂起态、终止态

### fork函数

创建一个子进程

pid_t fork(void) 失败返回-1,成功返回:1.父进程返回子进程的ID 2.子进程返回0
pid_t 类型表示进程ID，但为了表示-1,它是有符号整型
注意返回值，不是fork函数能返回两个值，而是fork后，fork函数变成两个，父子各需要返回一个

循环创建多个进程

使用for(i=0;i<5;i++){fork}创建子进程，这里注意加上条件判断 pid == 0 的话break掉子进程的循环，继续让父进程创建对应的子进程


### 进程共享的问题

父子进程之间在fork后，有哪些相同，哪些不同之处？

相同处：全局变量、.data .text 、栈、堆、环境变量、用户ID、宿主目录、进程工作目录、信号处理方式

不同处：进程ID、fork返回值、父进程ID、进程运行时间、闹钟、未决信号集

似乎，子进程复制了父进程0-3G用户空间的内容以及父进程的PCB，但pid不同

不是这样的，父子进程之间遵循读时共享写时复制的原则

无论子进程执行父进程的逻辑还是执行自己的逻辑都能节省内存开销

### exec函数族

fork创建子进程后执行的是和父进程相同的程序，子进程往往要调用一种exec函数以执行另一个程序。当进程调用一种exec函数的时候，该进程的用户空间代码和数据完全被新程序替换，从新程序的启动历程开始执行。调用exec并不创建新进程，所以调用exec前后该进程的id并未改变

将当前进程的.text、.data替换为所要加载程序的.text、.data,然后让进程从新的.text第一条指令开始执行，但进程ID不变，换核不换壳

Int execl(const *path,const char *arg)
Int execlp(const char *file,const char * arg)
Int execle(const char *party th,const char *arg,char *const envp[])
Int execv(const char *path,char *const argv[])
Int execvp(const char *file,char *const argv[])
Int execve(const char *path,char *const argv[],char *const envp[])

让子进程执行不同的程序，使用exec函数族

execlp函数

加载一个进程，借助PATH环境变量

int execlp(const char *file,cosnt char *arg) 成功:无返回；失败:-1

参数1:要加载的程序的名称。该函数需要配合PATH环境变量来使用。当PATH中所有目录搜索后没有参数1的话则出错返回

该函数通常用来调用系统程序。例如ls、date、cp、cat命令


execl函数

加载一个进程,通过路径+程序名来加载

int execl(const char *path,const char *arg) 成功:无返回，失败:-1

跟execlp的区别主要在于第一个参数是一个路径，而不是程序的名称

该函数主要用于加载自己自定义的程序



execvp函数

加载一个进程，使用自定义环境变量env

int execvp(const char *file,const char *argv[])

execvp与execlp参数形式不同，但原理是一样的

### 回收子进程

孤儿进程

父进程先于子进程结束，则子进程称为孤儿进程，子进程的父进程成为init进程

僵尸进程

进程终止，父进程尚未回收，子进程残留在PCB存放于内核中，变成僵尸进程

我们的测试代码其实都没有对子进程进行回收

wait函数

一个进程在终止的时候会关闭所有的文件描述符，释放在用户空间分配的内存，但是它的PCB还保留着，内核存了一些信息，如果是正常终止则保存着退出状态，如果是异常终止则保存着导致该进程终止的信号是哪个。

这个进程的父进程可以调用wait或者waitpid获取这些信息，然后彻底清除 这个进程。一个进程的退出状态可以在shell中用特殊的$?查看，因为shell是他的父进程，当它终止的时候shell调用wait或waitpid得到它的退出状态同时彻底清除这个进程。

父进程调用wait函数可以回收子进程终止信息，该函数有三个功能：

阻塞等待子进程退出

回收子进程的残留资源

获取子进程退出原因

pid_t wait(int *status)成功：清理的子进程ID，失败：-1没有子进程

当进程终止时候，操作系统的隐式回收机制：

关闭所有的文件描述符

释放用户空间分配的内存

PCB中保存用户的退出状态，正常退出—-> 退出值 异常终止——> 终止信号

可使用wait函数传出参数status来保存进程退出的状态，借助宏函数来进一步的判断进程终止的原因

WIFEXITED(status) 为非0 —-> 进程正常结束 

WEXITSTATUS(status) 如上宏真，使用此宏 —-> 获取进程退出状态

WIFSIGNALED(status) 为非0 ——> 进程异常终止

WTERMSIG(status)如上宏为真，使用此宏——> 取得使进程终止的信号编号

WIFSTOPPED(status) 为非0 ——-> 进程处于暂停状态

WSTOPSIG(status) 如上宏为真，使用此宏 ——-> 取得使进程暂停的信号编号

WIFCONTINUED(status) 为真——> 进程暂停后已经继续运行


waitpid函数（一次wait函数调用只能回收一个子进程，使用waitpid回收多个子进程）

作用同wait,但可指定pid进程清理，可以不阻塞

pid_t waitpid(pid_t pid,int *status,int options) 成功:返回清理掉的子进程ID；失败-1

特殊参数和返回情况：

参数pid:

	> 0 回收指定ID的子进程

	-1 回收任意子进程(相当于wait)

	0 回收和当前调用waitpid一个组的所有子进程

	< -1 回收指定进程组内的任意子进程

返回值: 0参数3为WNOHANG ,且子进程正在进行（设置参数3为轮询检查进程是否死亡非阻塞）


注意：一次wait或waitpid调用只能清理一个子进程，清理多个子进程应使用循环


## 2.进程间通信IPC方法

Liunx环境下，进程地址空间相互独立，每个进程各自有不同的用户地址空间。任何一个进程的全局变量在另一个进程中是看不到的，所以






