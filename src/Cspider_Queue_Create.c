#include<Cspider.h>


queue_t *Cspider_Queue_Create(int quemax)
{
	queue_t *q=(queue_t*)malloc(sizeof(queue_t));
	q->urlarr=(url_t*)malloc(sizeof(url_t)*quemax);
	q->front=0;
	q->rear=0;
	q->size=0;
	q->max=quemax;
	return q;
}
