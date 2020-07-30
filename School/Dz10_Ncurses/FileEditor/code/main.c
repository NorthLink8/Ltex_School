#include "main.h"


int x=0,y=0;
const int width = 100;
const int height = 40;

int ReadFile(FILE* _fp, uchar* _file, uchar** buffer)
{
  u32 lSize=0;
  size_t result;

  _fp=fopen(_file, "rw+");
  if(_fp<0)
  {
    perror("file open crash");
    //exit(EXIT_FAILURE);
  }
  fseek(_fp, 0, SEEK_END);
  lSize = ftell(_fp);
  rewind(_fp);

  *buffer = (uchar*)malloc(sizeof(uchar*)*lSize);
  if(buffer == NULL)
  {
    perror("Mem error");
    exit(EXIT_FAILURE);
  }
  result = fread(*buffer, 1, lSize, _fp);
  if(result != lSize)
  {
    perror("Read error");
    exit(EXIT_FAILURE);
  }
  /*
  for(u16 i=0; i<lSize; i++)
  {
    printf("%c", buffer[i]);
  }
  */
  fclose(_fp);
  return 0;
}
int WhatTheTask(WINDOW** _win)
{
  int ch = mvwgetch(*_win,y,x);
  return ch;
}
/*
int WriteFile(FILE* _fp, uchar* _file, uchar* _buffer)
{
  
  u32 lSize=0;
  size_t result;

  _fp=fopen(_file, "wb");
  if(_fp<0)
  {
    perror("file open crash");
    //exit(EXIT_FAILURE);
  }
  
  result = fwrite(_buffer, sizeof(uchar),strlen(_buffer), _fp);
  if(result<0)
    perror("After fwrite:");
  
  fclose(_fp);
  return 0;
}
*/
int WriteWindow(WINDOW* _win, uchar* _file)
{
  int WR;
  uchar c=0;
  int fd = open (_file, O_RDWR|O_CREAT|O_TRUNC|O_APPEND, 0644);
  if(fd<0)
    perror("File write:");
  for(u16 i=0; i<height-1; i++)
  {
    for(u16 j=0; j<width-1;j++)
    {
      c=mvwinch(_win, i,j) & A_CHARTEXT;
      write(fd, &c, 1);
    }
    write(fd, "\n", 1);
  }

}

int main(void)
{
  if(!initscr())
  {
    perror("Init ncurses error");
    exit(EXIT_FAILURE);
  }
  initscr();
  curs_set(1);
  refresh();
  keypad(stdscr, TRUE);
  
  
  FILE* fp;
  uchar* ReadBuf;
  ReadFile(fp, "./test/test.txt", &ReadBuf);
  
  int offsetx = (COLS-width);
  int offsety = (LINES-height);

  WINDOW* win = newwin(height, width, 0, 0);
  keypad(win, TRUE);
  //printw(ReadBuf);
  //wmvaddstr(win, 1, 1, ReadBuf);
  //box(win, 0,0);
  wprintw(win, ReadBuf);
 
  //refresh();
  wrefresh(win);
  //getch();

  while(1)
  {
    int _task=WhatTheTask(&win);
    if(_task=='\n')
    {
      WriteWindow(win, "./test/test.txt");
      break;
    }
    else if(_task=='\t')
    {
      break;
    }
    else if(_task == KEY_UP)
    {
      y--;
      if(y<=0)
        y=0;
    }
    else if(_task == KEY_DOWN)
    {
      y++;
      if(y>=height)
        y=height-1;
    }
    else if(_task == KEY_LEFT)
    {
      x--;
      if(x<=0)
        x=0;
    }
    else if(_task == KEY_RIGHT)
    {
      x++;
      if(x>=width)
        x=width-1;
    }
    


    /*
    else 
    {
      printf("%d\n", _task);
      sleep(5);
      break;
    }
    */
  }

  free(ReadBuf);
  delwin(win);
  endwin();  
  return 0;
}
