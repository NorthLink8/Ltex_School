#include "./main.h"

#define BUFSIZE (/*64*128*/10)
volatile off_t progress=0, max_progress=1;
//pthread_t t;

void* thread_proc(void* arg)
{
  unsigned char buffer[BUFSIZE];
  int in = open("./test/testfile.txt", O_RDONLY);
  if(in<0)
  {
    perror("In open:");
    exit(EXIT_FAILURE);
  }
  int out = open("./test2/testfile.txt", O_WRONLY|O_CREAT|O_TRUNC);
  if(out<0)
  {
    perror("Out open:");
    exit(EXIT_FAILURE);
  }
  struct stat st;
  fstat(in, &st);
  progress=0;
  max_progress=st.st_size;
  ssize_t bytes_read;
  while(/*bytes_read = */read(in, buffer, BUFSIZE)>0)
  {
    int t = write(out, buffer, BUFSIZE);
    //progress+=bytes_read;
    progress+=t;
  }
  //progress=max_progress;
  close(in);
  close(out);

  return 0;
}
void copy_indicate(/*int _progress, int _max_progress*/)
{
  while(progress<max_progress)
  {
    sleep(1);
    printf("%d:%d\n", progress, max_progress);
  }
}

void stat_file_copy()
{
  pthread_t t[2];
  pthread_create(&t[1], NULL, (void*)thread_proc, NULL);
  pthread_create(&t[0], NULL, (void*)copy_indicate, NULL);
  
  pthread_join(t[1], NULL);
  pthread_join(t[0], NULL);
}

int main(void)
{
  
  stat_file_copy();
  printf("Hello\n");
  
  //printf("Hellow!\n");
  return 0;
}
