#include<Cspider.h>


int Cspider_Queue_Notin(queue_t * que,const char*url)
{
	int i=que->rear;
	while(i%que->max!=que->front){
		if((strncmp(que->urlarr[i].surl,url,strlen(url)))==0)
		{
			printf("%s\n",que->urlarr[i].surl);
			return 0;
		}
		i++;
	}
	return 1;
}
