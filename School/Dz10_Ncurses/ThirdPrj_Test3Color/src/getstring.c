#include "../inc/getstring.h"

uchar* get_string(uint16_t *len)
{
	*len=0;
	uint16_t capacity=1;
	uchar* s=(uchar*)malloc(10*sizeof(uchar));
	uchar c=getchar();

	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(uchar*)realloc(s, capacity*sizeof(uchar));
		}
		c=getchar();
	}
	s[*len]='\0';
	return s;
}

