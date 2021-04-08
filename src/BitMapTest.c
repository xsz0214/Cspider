#include<Cspider.h>



int BitMapTest(BitMap*bm,size_t x)
{
	size_t index,num;
	index=x>>5;
	num=x%32;
	if(bm->_bits[index]&(1<<num)){
		return 0;
	}
	return -1;
}
