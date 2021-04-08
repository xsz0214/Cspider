#include<Cspider.h>



size_t RSHash(KeyValue str)
{
	size_t ch;
	size_t hash=0;
	size_t magic=63689;
	while(ch=(size_t)*str++)
	{
		hash=hash*magic+ch;
		magic*=378551;
	}
	return hash;
}
