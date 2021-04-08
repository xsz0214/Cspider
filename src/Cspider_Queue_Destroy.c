#include<Cspider.h>


int Cspider_Queue_Destroy(queue_t*que)
{
	free(que->urlarr);
	free(que);


	return 0;
}
