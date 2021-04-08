#include<Cspider.h>


void BloomFilterSet(BloomFilter*bf,KeyValue x)
{
	size_t hash1,hash2,hash3;
	hash1=bf->hashfunc1(x)%bf->_bm._range;
	hash2=bf->hashfunc2(x)%bf->_bm._range;
	hash3=bf->hashfunc3(x)%bf->_bm._range;
	BitMapSet(&bf->_bm,hash1);
	BitMapSet(&bf->_bm,hash2);
	BitMapSet(&bf->_bm,hash3);
}
