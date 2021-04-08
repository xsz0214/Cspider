#include<Cspider.h>


void BloomFilterDestory(BloomFilter*bf)
{
	assert(bf);
	BitMapDestroy(&bf->_bm);
}
