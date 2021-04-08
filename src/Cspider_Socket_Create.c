#include<Cspider.h>

int Cspider_Socket_Create(void)
{
	int spfd;
	struct sockaddr_in spaddr;
	bzero(&spaddr,sizeof(spaddr));
	spaddr.sin_family=AF_INET;
	spaddr.sin_port=htons(8000);
	spaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	spfd=socket(AF_INET,SOCK_STREAM,0);
	bind(spfd,(struct sockaddr*)&spaddr,sizeof(spaddr));
	printf("[2]socket create success..\n");
	return spfd;
}
