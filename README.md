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

Liunx环境下，进程地址空间相互独立，每个进程各自有不同的用户地址空间。任何一个进程的全局变量在另一个进程中是看不到的，所以进程和进程之间不能相互访问，要交换数据必须通过内核，在内核中开辟一块缓冲区，进程1把数据从用户空间拷贝到内核缓冲区，进程2再从内核缓冲区把数据读走，内核提供的这种机制叫做进程间通信(IPC interProcess Communication)

在进程间通信完成数据传递是需要借助操作系统提供的方法，例如文件、管道、信号、共享内存、消息队列、套接字等

现如今常用的进程间通信方式：

- 管道
- 信号
- 共享内存(不经过内核)
- 消息队列(不做过多的了解)
- 信号灯(不做过多的了解)
- 本地套接字(详情看liunx网络编程)

> 这里分析一个最为经典的问题，进程中有专门的共享内存的映射区域,这个区域的数据有个特点：他们通过MMU映射到物理内存的时候指向同一块物理内存，类似于程序中的类库、函数库,每个程序都使用,但内存中只保留一份。程序在编译阶段的时候会把这些类库放到共享内存的映射区域;

> 这块区域同时也可以使用shm(共享内存)的方式把同一块物理内存的数据映射到不同的进程中，实现不同进程之间的通信

> 而mmap有两种方式：1.映射内存，它把普通文件映射成实际物理内存页，访问他就和访问物理内存一样，跟shm(共享内存)的功能一样，2.mmap可以映射文件，普通的文件被映射到进程地址空间后，进程可以像访问普通内存一样对内存进行访问，不必调用read()/write()操作，它只是把文件映射到进程的地址空间内

### 管道

管道是一种最基本的IPC机制，作用于有血缘关系的进程之间，完成数据的传递。

1. 其本质是一个伪文件(实为内核缓冲区)
2. 由两个文件描述符引用，一个表示读端，一个表示写端
3. 规定数据从管道的写端流入管道，从读端流出

管道的原理：管道实则为内核使用环形队列机制，借助内核缓冲区(4K)实现，回忆一下父子进程之间读时共享写时复制的原则

管道的局限性：

1. 数据自己读不能自己写
2. 数据一旦被读走，便不在管道中存在，不可反复读
3. 由于管道采用半双工通信方式，因此，数据只能在一个方向流动
4. 只能在有公共祖先的进程间使用管道

### 共享内存

共享内存允许两个或多个进程共享一个给定的存储区，因为数据不需要来回复制，所以是最快的一种进程间的通信机制。共享内存可以通过mmap()映射普通文件机制实现，也可以通过系统共享shm实现。

mmap的机制：就是在磁盘上创建一个文件，每个进程存储器里面，单独开辟一个空间来进行映射。如果是多进程的话，不会对实际的物理内存消耗太多

shm的机制：每个进程的共享内存都直接映射到实际的物理内存里面去

> mmap保存到实际硬盘中，优点是存储量可以很大，缺点是读取和写入的速度比较慢;shm保存到内存中，访问速度比磁盘快，缺点是存储量不能太大

> 系统读取文件用的是read/write函数，将文件 -----> 内核 -----> 数据,但是mmap提供了一种不同的文件访问的方式，不经过内核

    void *mmap(void *adrr,size_t length,int prot,int flags,int fd,off_t offset);
    返回值：成功：返回创建的映射区首地址(应该是一个指针),失败:MAP_FAILED 宏
    参数:
        addr: 建立映射区的首地址，由liunx内核指定。使用的时候，直接传递NULL
        length:映射区的大小
        prot:映射区权限PROT_READ / PROT_WRITE / PROT_READ|PROT_WRITE
        flags:标志位参数
            MAP_SHARED : 会将映射区所做的操作反应到物理设备
            MAP_PRIVATE:映射区做的修改不会反应到物理设备
        fd:用来建立映射区的文件描述符
        offset：映射文件的偏移量(4K的整数倍)

munmap函数  

释放对应的mmap的空间，等同于malloc函数申请的内存空间

> 父子进程共享的内容：1.打开的文件(是因为内核的原因) 2.mmap建立的映射区(进程中的共享库的内存映射区域)

mmap实现进程之间通信

实质上,你可以观察下管道(有名管道),它是如何实现不同进程之间通信的，利用的还是文件，打开的文件描述符在进程之间是共享的,那么,mmap同样也要用到打开文件符,利用的也是同样的原理和操作，始终离不开文件,但是它跟文件之间还是有区别的，mmap的时候是不走内核的，速度更快

shm实现进程间通信

区别于mmap这个，它是直接映射同一段物理内存实现的进程间通信，跟文件这种形式是完全不一样的，因此也不用调用write/read函数

    int shmget(key_t key,int size,int shmflg);
    key:IPC_RPIVATE或者ftok的返回值
    size:共享内存的大小
    shmflg:同open函数的权限位,也可以用8进制表示法
    成功：共享内存段标识位 -- ID --- 文件描述符


ftok创建key值

    key_t  ftok(const char *path,char key)

    参数：第一个参数：文件路径和文件名
        第二个参数：一个字符
    返回值：正确返回一个KEy值，出错返回-1

    IPC_PRIVATE操作时，共享内存的Key值都一样，都是0 ,所以使用ftok来创建key值，只要key
    值是一样的，用户控件的进程通过这个函数打开，则会对内核的同一个IPC对象操作

Shmat 将共享内存映射到用户空间中的地址中

    void * shmat(int shmid,const void *shmaddr,int shmflg)

    参数：第一个参数：ID号
        第二个参数：映射到的地址，NULL为系统自动完成的映射
        第三个参数shmflg  SHM_RDONLY 共享内存只读，默认是0，表示共享内存可读写

    作用：在用户空间对共享内存进行操作，不需要直接再进入内核了
    返回值：成功：映射后的地址
    失败：NULL

Shmdt 将进程里的地址映射删除

    int shmdt(const void *shmaddr)
    参数：shmaddr共享内存映射后的地址
    返回值：成功0 失败-1

shctrl:删除共享内存对象

    函数原型：int shmctl(int shmid,int cmd,struct shmid_ds *buf);
    函数参数：shmid 要操作的共享内存标识符
            cmd:IPC_STAT 获取对象属性 IPC_SET 设置对象属性 IPC_RMID 删除对象
            buf:指定IPC_STAT/IPC_SET时用以保存/设置属性
    函数返回值：成功0 失败-1

> 总结：进程间通信,管道和mmap,一个走内核，一个不走内核，mmap和shm之间，一个映射磁盘，一个映射内存




### 信号

1. 信号的概念

信号在我们的生活中随处可见，如：古代战争中的摔杯为号，现代战争中的信号弹，体育比赛中的使用的信号枪。。。

他们都有共性：1. 简单 2.不能携带大量的信息  3. 满足某个特定条件才发送

信号的机制

A给B发送信号，B接收到信号之前执行自己的代码，收到信号后，不管执行到程序的什么位置，都要暂停运行，去处理信号，处理完毕后在继续执行。

这与硬件中断类似--异步模式。但信号是软件层次实现的终端，早起常被称为软中断

每个进程收到的信号，都是由内核负责发送出去的，内核进行处理

产生信号：

- 按键产生 如:ctrl+c ctrl+z ,ctrl+\
- 系统调用产生 如kill raise abort
- 软件条件产生,如定时器 alarm
- 硬件异常产生：如非法访问内存、除0
- 命令产生：如kill命令

递达：递送并且到达
未决：产生和抵达之间的状态，主要由于阻塞(屏蔽)导致该状态

信号的处理方式:

- 执行默认动作 
    - 终止进程
    - 终止进程且core文件
    - 忽略
    - 暂停stop
    - 继续
- 忽略(丢弃)
- 捕捉(掉处理函数)

阻塞信号集：将某些信号加入集合，对他们进行屏蔽，当屏蔽x信号后，再收到该信号，该信号的处理将推后

未决信号集：未决信号集中描述该信号的位立刻从0翻转为1，当信号被处理后立刻翻转回0，这一时刻非常的短暂。假设这时候信号被阻塞信号集阻塞，那么该信号又要从0翻转回1了。

> 总结：信号 ---> 未决信号集  ---> 阻塞信号集 ----> 递达


信号的四个要素：

- 编号
- 名称
- 事件
- 默认处理动作

可以通过man 7 signal 查看帮助文档，也可以通过/signal.h头文件查看


2. 产生信号的5种方式

终端按键产生信号

    ctrl+c ----> 终止、中断
    ctrl+z -----> 暂停、停止
    ctrl+\ -----> 退出

硬件异常产生信号

    除0操作 ---> 浮点数错误
    非法内存访问 ---> 段错误
    总线错误 ----> sigbus

kill函数/命令产生信号

kill命令产生信号:kill -SIGKILL PID

KILL函数：给指定的进程发送指定的信号

    int kill(pid_t pid,int sig) 成功0，失败-1
    sig:不推荐直接使用数字，应该使用宏名字
    pid > 0 :发送信号给指定的进程
    pid = 0 :发送信号给与调用Kill函数进程属于同一进程组的所有进程
    pid < 0 : 取pid发送给对应的进程组
    pid = -1:发送给进程有权限发送的系统中所有的进程
    进程组:每个进程都属于一个进程组，进程组是一个或多个进程集合，相互关联完成一个实体任务。每个进程组都有一个进程组长，进程组ID和进程组长ID相同


raise和abort函数

    raise函数：给当前进程发送指定的信号(自己给自己发)
    int raise(int sig)成功0，失败非0
    abort函数：给自己发送异常终止信号
    void abort(void) 无返回值

软件条件产生信号

    alarm函数 设置定时器，在指定的seconds后，内核会给当前进程发送信号，默认动作终止
    unsigned int alarm(unsigned int seconds) 返回0或剩余的秒数，无失败
    setitimer函数：设置定时器，可替代alarm函数，精度微秒，可实现周期定时
    int setitimer(int which,const struct itimerval *new_val,struct itimerval *old_value ) 成功0，失败-1
    参数which:指定定时方式
        自然定时 ITIMER_REAL
        虚拟空间定时 ITIMER_VIRTUAL
        运行时间定时 ITMER_PROF

3. 信号集操作函数

内核通过读取未决信号集来判断信号是否应被处理。信号屏蔽字mask可以影响未决信号集.

    sigset_t set;//自己定义的一个信号集合
    int sigemptyset(sigset_t *set) 信号集清0
    int sigfillset(sigset_t *set) 将某个信号集1
    int sigaddset(sigset_t *set,int signum) 将某个信号加入信号集,信号对应的编号变为1
    int sigdelset(sigset_t *set,in signum) 将某个信号清出信号集,信号对应的编号变为0
    int sigismember(const sigset_t *set,int signum) 判断某个信号是否在信号集中

顺序是 sigemptyset(&set) ---> sigaddset(&set,signum) ----> sigpromask(sig_block,&set) 阻塞信号集，这里，这里只是单纯的阻塞，好像没有后续的操作了....

sigprocmask函数

用来屏蔽信号。解除屏蔽，其本质，读取或者修改信号屏蔽字(阻塞信号集)

    int sigprocmask(int how,const sigset_t *set,sigset_t *oldset)，成功0,失败-1
    参数：
        set传入参数，是一个位图，set中哪位置1，就表示当前进程屏蔽哪个信号
        oldset传出参数，保存旧的信号屏蔽集
        how:假设当前的信号屏蔽字为mask
            1. sig_block : set表示需要屏蔽的信号
            2. sig_unblock:set表示需要解除的信号
            3. sig_setmask:set表示用于替代原始屏蔽集的新屏蔽集

4. 信号的捕捉

产生一个信号----> 未决信号集(内核递送中) ---> 阻塞信号集(内核递送中) ----> 捕捉(捕捉就按自己的方式处理) ----> 处理(默认方式)

signal函数

注册一个信号捕捉函数

    typedef void (*sighandler_t)(int);
    sighandler_t signal(int signum,sighandler_t handler);
    尽量避免使用这个函数，取而代之的是sigaction函数

sigaction函数

修改信号处理动作

    int sigaction(int signum,const struct sigaction *act,struct sigaction * oldact);
    参数:
        act:传入参数，新的处理方式
        oldact:传出参数，旧的处理方式

struct sigaction 结构体

    struct sigaction {
        void (*sa_handler)(int); //指定信号捕捉后的处理函数
        void (*sa_sigaction)(int,siginfo_t *,void *); //过时了
        sigset_t sa_mask;//需要屏蔽的信号即可，仅在运行中,这里不需要调用sigprocmask,直接emptyset-->addset即可
        int sa_flags;//通常设置为0
        void (*sa_restorer)(void) //过时了
    }

5. 竞态条件(时序竞态)

由于两个进程前后执行的顺序导致前后两次运行得到不同的结果

pause函数

调用该函数可以造成进程的主动挂起，等待信号唤醒。调用该系统调用的进程处于阻塞状态直到有信号递达将其唤醒

    int pause(void) 返回值：-1
    返回值：
        1.如果信号的默认处理动作是终止进程，则进程终止
        2.如果信号的默认处理动作是忽略，则进程继续处于挂起状态
        3.如果信号的处理动作是捕捉，则调用完信号处理函数之后,pause返回-1
        4.pause收到的信号不能被屏蔽，如果被屏蔽，则pause不能被唤醒


案例:使用pause和alarm函数实现mysleep()


    void catch_sigalarm(int signo){
        ;
    }
    unsigned int mysleep(unsigned int seconds){
        struct sigaction act,oldact;
        act.sa_handler = catch_sigalarm; //注册捕获函数
        sigemptyset(act.sa_mask);
        act.sa_flags = 0;
        sigaction(SIGALRM,&act,&oldact);//捕获信号
        alarm(seconds);//发送信号，几秒后发送sigalarm信号
        pause();//主动挂起,收到alarm信号后调用处理函数
        sigaction(SIGALRM,&oldact,NULL);//恢复alarm信号有一种默认处理方式，执行完后恢复
    }
    int main(void){
        while(1){
            mysleep(3);
            printf("---------------\n");
        }
        return 0;
    }

### 3. 进程组、会话、守护进程

进程组，也称之为作业。BSD于1980年前后向unix中增加了一个新的特性，代表一个或多个进程的集合。每个进程都属于一个进程组

在watpid函数和kill函数参数中都曾经有过。

当父进程创建子进程的时候，默认子进程和父进程是同一进程组。进程组ID == 第一个进程的ID

可以使用kill -SIGKILL - 进程组ID(负的)来将整个进程组的进程全部杀死

组长进程可以创建一个进程组，创建该进程组中的进程，然后终止，只要进程组中有一个进程存在，进程组就存在，与组长进程是否终止无关

进程组生存期：进程组创建到最后一个进程离开

一个进程可以为自己或者子进程设置进程组ID

进程组操作函数

    getpgrp函数
    获取当前进程的进程组id
    pid_t getpgrp(void) 总是返回调用者的进程组ID

    getpgid函数
    获取指定进程的进程组ID
    pid_t getpgid(pid_t pid) 成功0，失败-1

    setpgid函数
    改变进程默认的进程组ID，通常用于加入一个现有进程组或者创建一个新的进程组
    int setpgid(pid_t pid,pid_t pgid)
    将参数1对应的进程加入参数2对应的进程组中去


会话函数

创建一个会话需要注意：

    1. 调用进程不能是进程组组长，该进程变成新会话首进程
    2. 该进程称为一个新进程组的组长进程
    3. 需要root权限
    4. 新会话丢弃原有的控制终端，该会话没有控制终端
    5. 该调用进程是组长进程，则出错返回
    6. 建立新会话的时候，先调用fork，父进程终止，子进程调用setsid


getsid函数

    获取进程所属会话ID
    pid_t getsid(pid_t pid) 成功返回进程会话ID

setsid函数

    创建一个会话，并以自己的ID设置进程组ID，同时也是新会话的ID
    pit_t setsid(void)成功返回进程的会话ID
    调用setsid函数的进程，既是新的会长，也是新的组长

### 4.线程







































