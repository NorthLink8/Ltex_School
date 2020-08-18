#include "../inc/divide.h"

int _divide(long* result, long first, long second)
{
  if(second==0)
  {
    return 0;
    exit(EXIT_FAILURE);
  } 
  *result = first/second;
  return 0;
}
