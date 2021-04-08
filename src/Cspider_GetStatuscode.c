#include<Cspider.h>

int Cspider_GetStatuscode(char*reshead)
{
	int statuscode;
	char status[20];
	regex_t reg;       //正则表达式
	regmatch_t match[2]; 
	bzero(status,sizeof(status));
	regcomp(&reg,"HTTP/1.1 \\([^\r\n]\\+\\?\\)\r\n",0);
	if(regexec(&reg,reshead,2,match,0)==0){
		printf("500\n");
		snprintf(status,match[1].rm_eo - match[1].rm_so+1,"%s",reshead+match[1].rm_so);
		sscanf(status,"%d",&statuscode);
	}
	return statuscode;
}
