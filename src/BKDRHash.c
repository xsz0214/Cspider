#include<Cspider.h>


 size_t BKDRHash(const char *str)
{
	size_t seed =131;
	size_t hash =0;
	while(*str)
	{
		hash =hash*seed+(*str++);
	}
	return (hash&0x7FFFFFFF);
}
