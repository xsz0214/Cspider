#include<Cspider.h>



void BloomFilterTest(BloomFilter* bf,queue_t* wque,queue_t* qque,url_t url){
	BloomFilterInit(bf,10000);
	if((BloomFilterFind(bf,url.surl))==0){
		Cspider_Queue_Add(wque,url);
	}
/*	while(i<qque.size()){
		BloomFilterSet(&bf,wque[i].urlall->surl);
		i++;
	}*/
	BloomFilterDestory(bf);
}
