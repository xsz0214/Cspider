#include<Cspider.h>


int Cspider_Queue_Del(queue_t *que,url_t *node)
{
	if(que->size==0)
		return 0;//容器空则删除失败
//	printf("%d",que->front);
	*node=que->urlarr[que->rear];
    printf("del scussess surl=%s\n",node->surl);
	que->rear=(que->rear+1)%que->max;
	--que->size;
	
	return 1;
}
