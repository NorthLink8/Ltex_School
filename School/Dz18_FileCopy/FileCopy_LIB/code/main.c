#include "./main.h"

int main(void)
{
  int prog=0;
  _filecopy("./test/test.txt", "./test2/test.txt", &prog);
  //printf("Hello\n");
  //printf("%d\n", prog);
  return 0;
}
