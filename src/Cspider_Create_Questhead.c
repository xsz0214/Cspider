#include<Cspider.h>



int Cspider_Create_Requesthead(url_t*u,char* qhead)
{
	bzero(qhead,sizeof(qhead));
	sprintf(qhead,"GET %s HTTP/1.1\r\n"\
				"Accept:text/html,application/xhtml+xml,application/xml;q=0.9,image/webp,*/*;q=0.8\r\n"\
				"User-Agent:Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537(KHTML, like Gecko) Chrome/47.0.2526Safari/537.36\r\n"\
				"Host:%s\r\n"\
				"Connection:close\r\n\r\n",u->surl,u->domain);
	printf("[4]create requesthead success:\n%s\n",qhead);
	return 0;
}
