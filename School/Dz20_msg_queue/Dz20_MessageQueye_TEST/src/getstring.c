#include "../inc/getstring.h"

unsigned char* get_string(unsigned int *len, WINDOW* win)
{
	*len=0;
	unsigned int capacity=1;
	unsigned char* s=(uchar*)malloc(10*sizeof(unsigned char));
	unsigned char c=wgetch(win);
  wprintw((WINDOW*)win, "%c", c);
	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(unsigned char*)realloc(s, capacity*sizeof(unsigned char));
		}
		c=wgetch(win);
    wprintw((WINDOW*)win, "%c",c);
	}
	s[*len]='\0';
	return s;
}

