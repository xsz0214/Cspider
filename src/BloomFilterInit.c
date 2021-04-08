#include<Cspider.h>


void BloomFilterInit(BloomFilter*bf,size_t range)
{
	assert(bf);
	BitMapInit(&bf->_bm,range);
	bf->hashfunc1= BKDRHash;
	bf->hashfunc2= SDBMHash;
	bf->hashfunc3= RSHash;
}
