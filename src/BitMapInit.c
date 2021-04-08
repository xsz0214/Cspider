#include<Cspider.h>


void BitMapInit(BitMap*bm,size_t range)
{
	assert(bm);
	bm->_bits=(size_t*)malloc(sizeof(size_t)*((range>>5)+1));
	bm->_range=(range>>5)+1;
	memset(bm->_bits,0,sizeof(size_t)*((range>>5)+1));
}
