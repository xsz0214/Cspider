#include<Cspider.h>


int Cspider_Queue_Add(queue_t*que,url_t node)
{
	if(que->size==que->max)
		return 0;//容器满添加失败
	que->urlarr[que->front]= node;
    printf("queueadd 222 %s\n",que->urlarr[que->front].surl);
	que->front=(que->front+1)%que->max;
	++que->size;
		

	return 1;
}
