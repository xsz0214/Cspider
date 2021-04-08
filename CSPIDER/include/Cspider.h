#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<regex.h>
#include<openssl/err.h>
#include<openssl/ssl.h>
#include<sys/mman.h>
#include<pthread.h>
#include<errno.h>
#include<time.h>
#include<asm/types.h>
#include<assert.h>
int datefd;

typedef size_t(*HASH_FUNC)(const char*str);
typedef const char* KeyValue;
typedef struct
{
	char surl[4096];
	char domain[1024];
	char path[1024];
	char file[1024];
	char ip[16];
	int httptype;//0 http  1:https
	int port;
}url_t;

typedef struct
{
	SSL *sslsocket;
	SSL_CTX *sslctx;
}ssl_t;

typedef struct
{
	url_t* urlarr;
	int front;
	int rear;
	int size;
	int max;
}queue_t;

//封装一个互斥量和条件变量作为状态
typedef struct condition
{
	    pthread_mutex_t pmutex;
		pthread_cond_t pcond;
}condition_t;

typedef struct task
{
	void *(*run)(void *args);  //函数指针，需要执行的任务
	void *arg;              //参数
	struct task *next;      //任务队列中下一个任务
}task_t;


//下面是线程池结构体
typedef struct threadpool
{
	condition_t ready;    //状态量
	task_t *first;       //任务队列中第一个任务
	task_t *last;        //任务队列中最后一个任务
	int counter;         //线程池中已有线程数
	int idle;            //线程池中空闲线程数
	int max_threads;     //线程池最大线程数
	int quit;            //是否退出标志
}threadpool_t;

//构建位图
typedef struct 
{
	size_t* _bits;
	size_t  _range;
}BitMap;

//构建布隆过滤器
typedef struct 
{
	BitMap _bm;
	HASH_FUNC hashfunc1;
	HASH_FUNC hashfunc2;
	HASH_FUNC hashfunc3;
}BloomFilter;


size_t BKDRHash(const char *);
size_t SDBMHash (KeyValue);
size_t RSHash (KeyValue);

void BitMapInit (BitMap*,size_t);
void BitMapSet  (BitMap*,size_t);
void BitMapReset(BitMap*,size_t);
void BitMapDestroy(BitMap*);
int BitMapTest(BitMap*,size_t);

void BloomFilterInit (BloomFilter*,size_t);
void BloomFilterSet  (BloomFilter*,KeyValue);
void BloomFilterReset(BloomFilter*,KeyValue);
void BloomFilterTest(BloomFilter*,queue_t*,queue_t*,url_t );
void BloomFilterDestory(BloomFilter*);
int BloomFilterFind(BloomFilter*,char *);

int Cspider_Analytical_Url(url_t*);    //解析
int Cspider_Socket_Create(void);//创建SOCKET并初始化
int Cspider_Connect_Webserver(url_t*,int);//链接Web服务器
int Cspider_Create_Requesthead(url_t*,char *);//创建请求头
int Cspider_Download(url_t*,char*,int,ssl_t*);//资源请求与下载
int Cspider_GetStatuscode(char*);//获取响应头
int Cspider_Analytical_Html(url_t*,queue_t*,queue_t*);//匹配抽取网页源码队关健数据
int Cspider_Savedata(const char*,const char *,const char*);//将关键数据格式化存储到指定文件中
ssl_t* Cspider_Create_Openssl(int);//创建认证https安全认证

queue_t* Cspider_Queue_Create(int);
int Cspider_Queue_Add(queue_t*,url_t);
int Cspider_Queue_Del(queue_t*,url_t*);
int Cspider_Queue_Notin(queue_t*,const char *);
int Cspider_Queue_Destroy(queue_t*);

int condition_init(condition_t *);//初始化
int condition_lock(condition_t *);//加锁
int condition_unlock(condition_t *);//解锁
int condition_wait(condition_t *);//等待
int condition_timedwait(condition_t *, const struct timespec *);//固定时间等待
int condition_signal(condition_t* );//唤醒一个睡眠线程
int condition_broadcast(condition_t *);//唤醒所有睡眠线程
int condition_destroy(condition_t *);//释放
//创建队线程执行
void *thread_routine(void*);

//线程池初始化
void threadpool_init(threadpool_t *, int );

//往线程池中加入任务
void threadpool_add_task(threadpool_t *, void *(*run)(void *), void *);

//摧毁线程池
void threadpool_destroy(threadpool_t *);
//任务
void* mytask(void *,queue_t* ,queue_t* ,url_t ,char* ,ssl_t*);

