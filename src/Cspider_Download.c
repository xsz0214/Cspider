#include <Cspider.h>



int Cspider_Download(url_t * u , char * qhead, int webfd , ssl_t * ssl)
{
		int len;
		char buf[8192];
		char rehead[4096];
		char * pos;
		int fd;
		int status;
		bzero(buf,sizeof(buf));
		bzero(rehead,sizeof(rehead));
		if(!ssl){
				/* send request */
				send(webfd,qhead,strlen(qhead),0);
				printf("[5] Send requesthead success..\n");
				/* get reshead */
				len = recv(webfd,buf,sizeof(buf),0);
				if((pos = strstr(buf,"\r\n\r\n"))==NULL){
						perror("strstr Call Failed");
						return -1;
				}
				snprintf(rehead,pos - buf + 4,"%s",buf);
				printf("[6] Get responsehead success:\n%s",rehead);
				if((status = Cspider_GetStatuscode(rehead))==200){
						printf("Get Response StatusCode [%d]\n",status);
						/* download file */
						fd = open(u->file,O_RDWR|O_CREAT,0775); //某些资源文件需要执行权限
						write(fd,pos+4,len - (pos - buf + 4));

						while((len = recv(webfd,buf,sizeof(buf),0))>0)
								write(fd,buf,len);
						printf("[7] download file success..\n");
				}else{
						printf("Get Response StatusCode [%d]\n",status);
						return -1;
				}
		}else{
				SSL_write(ssl->sslsocket,qhead,strlen(qhead));
				printf("[5] SSL Send requesthead success..\n");
				len = SSL_read(ssl->sslsocket,buf,sizeof(buf));
				printf("%d\n",len);	
				if((pos = strstr(buf,"\r\n\r\n"))==NULL){
						perror("strstr Call Failed");
						return -1;
				}
				snprintf(rehead,pos - buf + 4,"%s",buf);
				printf("[6] SSL Get responsehead success:\n%s",rehead);
				if((status = Cspider_GetStatuscode(rehead))==200){
						printf("SSL Get Response StatusCode [%d]\n",status);
						fd = open(u->file,O_RDWR|O_CREAT,0775); //某些资源文件需要执行权限
						write(fd,pos+4,len - (pos - buf + 4));

						while((len = SSL_read(ssl->sslsocket,buf,sizeof(buf)))>0)
								write(fd,buf,len);
						free(ssl);
						ssl = NULL;
						printf("[7] SSL download file success..\n");

				}else{
						printf("SSL Get Response StatusCode [%d]\n",status);
						return -1;

				}
		}
		close(webfd);
		return 0;
}
