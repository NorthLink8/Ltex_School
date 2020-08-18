#include "./main.h"

int main(void)
{
  printf("Hello\n");
  pid_t _pid;
  int rv;
  int fid[2];
  _pid=fork();
  if(_pid==0)
  {
    int _fw=open("./Write/writefile.txt", O_WRONLY|O_APPEND, 0644);
    if(_fw<0)
    {
      perror("OPEN writefile.txt error _1");
      exit(EXIT_FAILURE);
    }
    printf("ENTER YOUR PASSWORD (No more then 20 symbols)\n");
    unsigned int g=50;
    if(pipe(fid)<0)
      perror("pipe error");
    dup2(_fw,1);//Заменили ввод с клавиатуры на экран в указаный выше файл
    
    unsigned char* str=get_string(&g);
    printf("%s\n",str);
    exit(rv);
  }
  else
  {
    wait(&rv);
    int _fr=open("./Write/writefile.txt", O_RDONLY);
    if(_fr<0)
    {
      perror("FILE READ error PASS");
      exit(EXIT_FAILURE);
    }
    unsigned char buf[1];
    size_t bytesread;
    printf("READ FILE\n");
    while((bytesread=read(_fr, buf, 1))>0)
    {
      printf("%c", buf[0]);
    }
  }
  
  return 0;
}
