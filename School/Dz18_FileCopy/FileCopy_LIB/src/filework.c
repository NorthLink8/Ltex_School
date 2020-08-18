#include "../inc/filework.h"

volatile off_t realstatus=0, maxstatus=100;

static void* _COPY(void* namebuf)
{
  unsigned char buffer[1];
  unsigned char path_buffer[2][PATH_MAX];
  unsigned char* _namebuf=(unsigned char*)namebuf;
  
  for(unsigned k=0; k<PATH_MAX*2; k++)
  {
    if(k<PATH_MAX)
      path_buffer[0][k]=_namebuf[k];
    else
      path_buffer[1][k-PATH_MAX]=_namebuf[k];
  }
  //printf("IN name:%s\n", path_buffer[0]);
  //printf("OUT name:%s\n", path_buffer[1]);
  int in=open(path_buffer[0], O_RDONLY);
  //if(in<0)
    perror("IN:");
  int out=open(path_buffer[1], O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0644);
  //if(out<0)
    perror("OUT:");

  struct stat st;
  fstat(in, &st);
  realstatus=0;
  maxstatus=st.st_size;
  ssize_t bytes_read;
  if(st.st_size<8192)
  {
  }
  while((bytes_read=read(in, buffer, 1))>0)
  {
    write(out, buffer ,1);
    realstatus+=bytes_read;
  }
  realstatus=maxstatus;
  close(in);
  close(out);

  return(void*)0;
}

static void* _STATUS(void** param)
{
  while(realstatus<=maxstatus)
  {
    int _param=(realstatus/(maxstatus/100));
    printf("%d/100\n", _param);
    sleep(0.3);
    if(realstatus>=maxstatus)
    {
      _param=100;
      printf("%d/100\n", _param);
      *param=*(void**)&_param;
      break;
    }
  }
  return (void*)0;
}

void* _filecopy(unsigned char* path1, unsigned char* path2, int* result)
{
  pthread_t _tid[2];
  
  int len1=strlen(path1);
  int len2=strlen(path2);
  unsigned char path_buf[PATH_MAX*2];
  for(unsigned f=0; f<len1+len2; f++)
  {
    if(f<len1)
      path_buf[f]=path1[f];
    else
      path_buf[PATH_MAX+f-len1]=path2[f-len1];
  }
  pthread_create(&_tid[0], NULL, (void*)_COPY, path_buf);
  pthread_create(&_tid[1], NULL, (void*)_STATUS, result);
  //_STATUS((void**)&result);
  
  pthread_join(_tid[0], NULL);
  pthread_join(_tid[1], NULL);
  
  return (void*)0;
  
}
