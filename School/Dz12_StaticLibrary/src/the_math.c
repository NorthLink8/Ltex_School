#include "../inc/the_math.h"

int _plus(long* result, long first, long second)
{
  *result = first+second;
  return 0;
}

int _minus(long* result, long first, long second)
{
  *result = first-second;
  return 0;
}

int _multiply(long* result, long first, long second)
{
  *result = first*second;
  return 0;
}
int _divide(long* result, long first, long second)
{
  if(second==0)
  {
    return 1;
    exit(EXIT_FAILURE);
  }
  *result = first/second;
  return 0;
}
int _pow(long* result, long number, int degree)
{
  if(number==0 && degree==0)
  {
    return 1;
    exit(EXIT_FAILURE);
  }
  else if(number==0 && degree!=0)
  {
    *result=0;
    return 0;
  }
  else if(number!=0 && degree==0)
  {
    *result=1;
    return 0;
  }
  else
  {
    *result=number;
    for(u16 i=1; i<degree; i++)
    {
      *result*=number;
    }
    return 0;
  }
}
