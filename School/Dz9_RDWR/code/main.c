#include "main.h"



//O_RDWR    ReadWrite
//O_CREAT   Create new file
//O_APPEND  If set, the file offset shall be set to the end of the file prior to each write


int WR=0;


int main(void)
{
  printf("RDWR_secondPrj\n");
  
  
  int fd = open("./test/test.txt", O_RDWR|O_CREAT|O_TRUNC|O_APPEND, /*"w+"*/0644);

  if(fd<0)
  {
    perror("File write");
    //exit(EXIT_FAILURE);
  }
  
  //lseek(fd, 5, SEEK_CUR);

  WR = write(fd, "HelloFromFile\n", strlen("HelloFromFile\n"));
  if(WR<0)
    perror("After write:");
  
  close(fd);//Неявное описание функции

  
  fd = open("./test/test.txt", O_RDONLY, 0644);
  if(fd<0)
    perror("File read");
  
  //lseek(fd, 0, 0);
  uchar buffer[10];
  WR = read(fd, buffer, 10);
  if(WR<0)
    perror("After read:");
  for(u8 i=0; i<strlen(buffer); i++)
    printf("%c", buffer[i]);
  printf("\n");
  close(fd);
  

  return 0;
}
