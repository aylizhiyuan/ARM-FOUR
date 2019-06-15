#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <stdio.h>
struct msg {
    struct msg *next;
    int num;
};
struct msg *head;
struct msg *mp;

//静态初始化 一个条件变量和一个互斥量
pthread_cond_t has_product = PTHREAD_COND_INITIALIZER;
pthread_mutex_t lock = PTHREAD_MUTEX_INITIALIZER;

void *consumer(void *p){
    for(;;){
        
        pthread_mutex_lock(&lock);
        //头指针为空，说明没有任务
        while(head == NULL){
            //调用wait去阻塞等待被唤醒....
            //加过的锁也解锁了
            pthread_cond_wait(&has_product,&lock);
        }
        mp = head;
        head = mp->next;
        pthread_mutex_unlock(&lock);
        printf("--Consume---%d\n",mp->num);
        free(mp);
        sleep(rand() % 5);
    }
}
void *producer(void *p){
    for(;;){
        mp = malloc(sizeof(struct msg));
        mp->num = rand() % 100 + 1;
        printf("--Produce---%d\n",mp->num);
        pthread_mutex_lock(&lock);
        mp->next = mp;
        head = mp;
        pthread_mutex_unlock(&lock);
        //发送一个信号，唤醒线程
        pthread_cond_signal(&has_product);
        sleep(rand() % 5);
    }
}
int main(int argc,char *argv[]){
    pthread_t pid,cid;
    srand(time(NULL));
    pthread_create(&pid,NULL,producer,NULL);
    pthread_create(&cid,NULL,consumer,NULL);
    pthread_join(pid,NULL);
    pthread_join(cid,NULL);
    return 0;
}


