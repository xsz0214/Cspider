#include<Cspider.h>



int Cspider_Connect_Webserver(url_t*u,int webfd)
{
	struct sockaddr_in webaddr;
	bzero(&webaddr,sizeof(webaddr));
	webaddr.sin_family=AF_INET;
	webaddr.sin_port=htons(u->port);
	inet_pton(AF_INET,u->ip,&webaddr.sin_addr.s_addr);
	if((connect(webfd,(struct sockaddr*)&webaddr,sizeof(webaddr))==0)){
		printf("[3]connect webserver success..\n");
	}
	else
	{

		perror("[3]connect call failed");
		return -1;
	}
	return 0;
}
