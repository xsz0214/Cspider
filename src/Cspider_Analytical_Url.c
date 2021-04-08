#include <Cspider.h>


int Cspider_Analytical_Url(url_t * u)
{
		int i,j,start,filesize=0;
		char * arr[]={"http://","https://",NULL};
		/*init url_t*/
		bzero(u->path,sizeof(u->path));
		bzero(u->domain,sizeof(u->domain));
		bzero(u->file,sizeof(u->file));
		bzero(u->ip,sizeof(u->ip));

		/*get htttype*/
		if(strncmp(u->surl,arr[0],strlen(arr[0]))==0){
				u->httptype = 0;
				u->port = 80;
				start = strlen(arr[0]);
		}else{
				u->httptype = 1;
				u->port = 443;
				start = strlen(arr[1]);
		}
		/*get domain*/
		j=0;
		for(i=start;u->surl[i]!='/' && u->surl[i]!='\0';i++){
				u->domain[j] = u->surl[i]	;
				j++;
		}
		/*get file*/
		j=0;
		for(i=strlen(u->surl);u->surl[i]!='/';i--,filesize++);
		for(i=strlen(u->surl)-filesize + 1;u->surl[i]!='\0';i++){
				u->file[j] = u->surl[i];
				j++;
		}
		/*get path*/
		j=0;
		for(i=start + strlen(u->domain);i<strlen(u->surl) - filesize + 1;i++){
			u->path[j] = u->surl[i];
			j++;
		}
		/*get ip  call gethostbyname*/
		struct hostent * ent;
		if((ent = gethostbyname(u->domain))!=NULL){
				inet_ntop(AF_INET,ent->h_addr_list[0],u->ip,sizeof(u->ip));
		}else{
			perror("Call GethostByName Failed");
			exit(0);
		}
		printf("url success\n");
		printf("[1] Url Analytical success: [domain:%s] [path:%s] [file:%s] [ip:%s] [type:%d] [port:%d]\n",u->domain,u->path,u->file,u->ip,u->httptype,u->port);

		return 0;
}
