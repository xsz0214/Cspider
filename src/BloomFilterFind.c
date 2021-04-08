#include<Cspider.h>



int BloomFilterFind(BloomFilter*bf,char* x)
{
	size_t hash1,hash2,hash3;
	hash1=bf->hashfunc1(x)%bf->_bm._range;
	hash2=bf->hashfunc2(x)%bf->_bm._range;
	hash3=bf->hashfunc3(x)%bf->_bm._range;

	if(BitMapTest(&bf->_bm,hash1)==-1)
		return -1;
	
	if(BitMapTest(&bf->_bm,hash2)==-1)
		return -1;
	if(BitMapTest(&bf->_bm,hash3)==-1)
		return -1;

	return 0;
}
