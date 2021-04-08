#include <Cspider.h>


int Cspider_Savedata(const char *h1 ,const char *desc ,const char * url)
{
		char item_url[4096];
		bzero(item_url,4096);
		write(datefd,"<html>",strlen("<html>"));
		write(datefd,"<head><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\"></head>",strlen("<head><meta http-equiv=\"content-type\" content=\"text/html;charset=utf-8\"></head>"));
		write(datefd,"<body>",strlen("<body>"));
		write(datefd,"<div style='width:1360px;display:block;word-break:break-all;word-wrap:break-word;white-space:pre-wrap;'>",strlen("<div style='width:1360px;display:block;word-break:break-all;word-wrap:break-word;white-space:pre-wrap;'>"));
		write(datefd,"<h2>",strlen("<h2>"));
		write(datefd,h1,strlen(h1));
		write(datefd,"</h2>",strlen("</h2>"));
		write(datefd,"<h5>",strlen("<h5>"));
		write(datefd,desc,strlen(desc));
		write(datefd,"</h5>",strlen("</h5>"));
		snprintf(item_url,strlen(url) * 2+16,"<a href=\"%s\">%s</a>",url,url);
		write(datefd,item_url,strlen(item_url));
		write(datefd,"</div>",strlen("</div>"));
		write(datefd,"</body>",strlen("</body>"));
		write(datefd,"</html>",strlen("</html>"));
		printf("10savedate success\n");
		return 0;
}
