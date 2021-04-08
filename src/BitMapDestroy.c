#include<Cspider.h>


void BitMapDestroy(BitMap*bm)
{
	free(bm->_bits);
}
