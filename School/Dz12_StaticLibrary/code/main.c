#include "main.h"


int main(void)
{
  long res=5;
  _plus(&res, 10, 20);
  printf("%ld+%ld=%ld\n", 10,20,res);
  
  _minus(&res, 986545678,87654567);
  printf("%ld-%ld=%ld\n", 986545678,87654567, res);
  
  _multiply(&res, 10, 80);
  printf("%ld*%ld=%ld\n", 10,80,res);

  _divide(&res, 80,10);
  printf("%ld/%ld=%ld\n", 80,10,res);

  _pow(&res, 2,10);
  printf("%ld^%ld=%ld\n", 2,10,res);
  
  //while(1);
  return 0;
}
