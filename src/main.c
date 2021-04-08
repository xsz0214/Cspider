#include<Cspider.h>
#include <stdio.h>
#define MSIZE 1000
#define QSIZE 10000
#define TIMEOUT 100000

int main(void)
{
	int webfd;
	int code1;
	url_t node;
	url_t tmp;
	char head[4096];
	ssl_t* ssl=NULL;
    BloomFilter* bf;
	//首先处理url种子
	char *tmpurl="https://baike.baidu.com/item/%E7%8C%B4%E5%AD%90/1593453?fr=aladdin";
	//创建关健资源文件
	datefd=open("resdata.html",0,O_RDWR|O_CREAT,0775);
	strcpy(tmp.surl,tmpurl);
	//容器创建与初始化
	queue_t* wque= Cspider_Queue_Create(MSIZE);
	queue_t* qque= Cspider_Queue_Create(QSIZE);
	//将种子URL添加到URL容器去重判断
	BloomFilterTest(bf,wque,qque,tmp);
/*	if((Cspider_Queue_Notin(wque,tmp.surl)&&Cspider_Queue_Notin(qque,tmp.surl)))
	{
		Cspider_Queue_Add(wque,tmp);
//		printf("%s",wque[0].surl);
	}*/
	BKDRHash("SSI");
	//让资源下载工作拓扑持续
  	threadpool_t pool;
    //初始化线程池，最多三个线程
    threadpool_init(&pool, 3);
	while(wque->size>0){
		int *arg = malloc(sizeof(int));
		for(int i=1;i<5;i++){
			printf("%d\n",i);
			threadpool_add_task(&pool, mytask(NULL,wque,qque,tmp,head,ssl), arg);
		}
      // 	mytask(void *arg,queue_t* wque,queue_t* qque,url_t node,char* head,ssl_t* ssl);
/*	   	Cspider_Analytical_Url(&tmp);
//	   	printf("url:%s\n",tmp.surl);
		//mytask(NULL,wque,qque,tmp,head,ssl);
		threadpool_add_task(&pool, mytask(NULL,wque,qque,tmp,head,ssl), arg);
		//创建爬虫SOCKET
		webfd=Cspider_Socket_Create();
		//从未处理容器中获取一个url
		//Cspider_Analytical_Url(&tmp);
	//	Cspider_Queue_Add(qque,tmp);
		Cspider_Queue_Del(wque,&node);
		//解析url
		Cspider_Analytical_Url(&node);
		//与web服务器进行网络链接
		Cspider_Connect_Webserver(&node,webfd);
		//构造HTTP请求头
		Cspider_Create_Requesthead(&node,head);
		//判断协议类型 创建ssl
		if(node.httptype){
			printf("%d\n",node.httptype);
			ssl=Cspider_Create_Openssl(webfd);
		}
		//资源下载过程
		if((Cspider_Download(&node,head,webfd,ssl))==-1){
			printf("download success\n");
			continue;
		}
		//添加到已处理容器
		Cspider_Queue_Add(qque,node);
		Cspider_Analytical_Html(&node,wque,qque);
		usleep(10000);	*/
	}
	threadpool_destroy(&pool);
	close(webfd);
	return 0;
}
