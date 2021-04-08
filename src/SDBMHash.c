#include<Cspider.h>


size_t SDBMHash(KeyValue str)
{
	size_t ch;
	size_t hash=0;
	while(ch=(size_t)*str++)
	{
		hash=65599*hash+ch;
		//hash=(size_t)ch+(hash<<6)+(hash<<1)
	}
	return hash;
}
