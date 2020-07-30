#include "../inc/getstring.h"

uchar* getstring(u16 *len)
{
  *len=0;
  u16 capacity=1;
  uchar* s=(uchar*)malloc(50 * (u8)sizeof(uchar));
  uchar c=getchar();

  while(c!='\n')
  {
    s[(*len)++]=c;
    if(*len>=50)
    {
      capacity*=2;
      s=(uchar*)realloc(s, capacity* (u16)sizeof(uchar));
    }
    c=getchar();
  }
  s[*len]='\0';
  return s;
}
