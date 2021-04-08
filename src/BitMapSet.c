#include<Cspider.h>


void BitMapSet(BitMap* bm,size_t x)
{
	size_t index,num;
	index=x>>5;
	num=x%32;
	bm->_bits[index]|=(1<<num);
}
