#include "../inc/filework.h"
volatile off_t realstatus=0, maxstatus=100;
/*
  STRUCT must have:
  *LINE (unsigned int)
  *COL  (unsigned int)
  *(WINDOW*)
*/
struct copyStruct
{
  unsigned char* path1;
  unsigned char* path2;
};
struct printStruct
{
  unsigned int line;
  unsigned int col;
  WINDOW* _win;
};

static void* _COPY(void* _copyStruct)
{
  realstatus=0;
  unsigned char* buffer[1];
  int in=open(((struct copyStruct*)_copyStruct)->path1, O_RDONLY);
  if(in<0)
  {
    perror("IN");
    realstatus=maxstatus;
    return (void*)1;
  }
  int out=open(((struct copyStruct*)_copyStruct)->path2, O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0644);
  if(out<0)
  {
    perror("OUT");
    realstatus=maxstatus;
    return (void*)1;
  }
  
  struct stat st;
  fstat(in, &st);
  realstatus=0;
  maxstatus=st.st_size;

  ssize_t bytes_read;
  while((bytes_read=read(in, buffer, 1))>0)
  {
    write(out, buffer, 1);
    realstatus+=bytes_read;
  }
  realstatus=maxstatus;
  close(in);
  close(out);

  return(void*)0;
}

void* _STATUS(void** param)
{
  while(realstatus<maxstatus)
  {
    int _param=(realstatus/(maxstatus/100));
    sleep(0.3);
    *param=*(void**)&_param;
  }
  return(void*)0;
}

void* _printSTATUS(void* _printStruct)
{
  int _param=0;
  mvwprintw((((struct printStruct*)_printStruct)->_win),
              (((struct printStruct*)_printStruct)->line),
              (((struct printStruct*)_printStruct)->col+10), "[--------------------]");
  while(_param<100)
  {
    _param=(realstatus/(maxstatus/100));
    sleep(0.3);
    //mvwprintw(win, count, 3, "./%s", dir->d_name);
    mvwprintw((((struct printStruct*)_printStruct)->_win), 
              (((struct printStruct*)_printStruct)->line), 
              (((struct printStruct*)_printStruct)->col), "%d%/100%", _param);
    
    for(unsigned d=1; d<=_param/5; d++)
    {
      mvwprintw((((struct printStruct*)_printStruct)->_win),
                (((struct printStruct*)_printStruct)->line),
                (((struct printStruct*)_printStruct)->col+10+(d)), "*");
      wrefresh  (((struct printStruct*)_printStruct)->_win);
    }
  }
  sleep(1);
  //_param=(realstatus/(maxstatus/100));
  mvwprintw((((struct printStruct*)_printStruct)->_win), 
            (((struct printStruct*)_printStruct)->line), 
            (((struct printStruct*)_printStruct)->col), "                                  ", _param);
  wrefresh  (((struct printStruct*)_printStruct)->_win);
  
  realstatus=0;
}

void* _filecopy(unsigned char* _path1, unsigned char* _path2, WINDOW* window, unsigned int _line, unsigned int _col)
{
  pthread_t _tid[2];
  /*
  unsigned int len1=strlen(path1);
  unsigned int len2=strlen(path2);
  unsigned char path_buf[PATH_MAX*2];
  for(unsigned f=0; f<len1+len2; f++)
  {
    if(f<len1)
      path_buf[f]=path1[f];
    else
      path_buf[PATH_MAX+f-len1]=path2[f-len1];
  }
  */
  //struct printStruct
  struct copyStruct* copystr=(struct copyStruct*)malloc(sizeof(struct copyStruct));
  struct printStruct* printstr=(struct printStruct*)malloc(sizeof(struct printStruct));
  printstr->_win=window;
  printstr->line=_line;
  printstr->col=_col;
  copystr->path1=_path1;
  copystr->path2=_path2;


  //pthread_create(&_tid[1], NULL, (void*)_printSTATUS, (void*)str);
  pthread_create(&_tid[0], NULL, (void*)_COPY, (void*)copystr);
  pthread_create(&_tid[1], NULL, (void*)_printSTATUS, (void*)printstr);

  pthread_join(_tid[0], NULL);
  pthread_join(_tid[1], NULL);
}
