#include <Cspider.h>

int Cspider_Analytical_Html(url_t * u , queue_t * wque, queue_t * qque)
{
		int fd;
		int filesize;
		char * string;
		char desc[4096];
		char title[1024];
		char aurl[4096];
		char * jstr;
		url_t node;
		regex_t dreg,treg,areg;
		regmatch_t dmatch[2];
		regmatch_t tmatch[2];
		regmatch_t amatch[3];
		fd = open(u->file,O_RDONLY);
		filesize = lseek(fd,0,SEEK_END);
		string = mmap(NULL,filesize,PROT_READ,MAP_PRIVATE,fd,0);

		jstr = string;
		close(fd);
		/* 匹配标题 描述 链接*/
		regcomp(&dreg,"<meta name=\"description\" content=\"\\([^\"]\\+\\?\\)\"",0);
		regcomp(&treg,"<h1 >\\([^<]\\+\\?\\)</h1>",0);
		regcomp(&areg,"<a[^>]\\+\\?href=\"\\(/item/[^\"]\\+\\?\\)\"[^>]\\+\\?>\\([^<]\\+\\?\\)</a>",0);
		if((regexec(&dreg,string,2,dmatch,0))==0)
				printf("100\n");
				snprintf(desc,dmatch[1].rm_eo - dmatch[1].rm_so + 1,"%s",string + dmatch[1].rm_so);
		if((regexec(&treg,string,2,tmatch,0))==0)
				printf("200\n");
				snprintf(title,tmatch[1].rm_eo - tmatch[1].rm_so + 1,"%s",string + tmatch[1].rm_so);
		if(wque->size <= 10)
				printf("300\n");
				while((regexec(&areg,string,3,amatch,0))==0){
						snprintf(aurl,amatch[1].rm_eo - amatch[1].rm_so + 24,"https://baike.baidu.com%s",string + amatch[1].rm_so);
						/* 将解析出的新链接加入未处理容器 等待处理*/
						if(Cspider_Queue_Notin(wque,aurl) && Cspider_Queue_Notin(qque,aurl))
						{
								strcpy(node.surl,aurl);
								printf("new url [%s]\n",aurl);
								Cspider_Queue_Add(wque,node);
						}

						string += amatch[0].rm_eo;
						bzero(aurl,sizeof(aurl));
				}
		Cspider_Savedata(title,desc,u->surl);
		printf("title[%s]\n",title);
		printf("desc[%s]\n",desc);
		regfree(&dreg);
		regfree(&treg);
		munmap(jstr,filesize);
		unlink(u->file);
		return 0;
}
