#include<Cspider.h>
void* mytask(void *arg,queue_t* wque,queue_t* qque,url_t node,char* head,ssl_t* ssl)
{
  int  webfd=Cspider_Socket_Create();
  //从未处理容器中获取一个url
  Cspider_Queue_Del(wque,&node);
  printf("uuuuu=%s\n",node.surl);
  //解析url
  Cspider_Analytical_Url(&node);
  //与web服务器进行网络链接
  Cspider_Connect_Webserver(&node,webfd);
  //构造HTTP请求头
  Cspider_Create_Requesthead(&node,head);
  //判断协议类型 创建ssl
  if(node.httptype){
	  ssl=Cspider_Create_Openssl(webfd);
	  }
	  //资源下载过程
  if((Cspider_Download(&node,head,webfd,ssl))==-1){
 		  return NULL;
	 }
	 //添加到已处理容器
  	Cspider_Queue_Add(qque,node);
     Cspider_Analytical_Html(&node,wque,qque);
	 usleep(100000);
    free(arg);
    return NULL;
}
