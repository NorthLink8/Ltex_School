#include "main.h"



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

int WriteFile(FILE* _fp, uchar* _file, uchar** _strbuf)
{
  return 0;
}

int WhatTheTask()
{
  int ch = getch();
  if(ch == '\t')
  {
    //save file
    return 1;
  }
  else if (ch == KEY_BACKSPACE)
  {
    //Don't save file and quit
    return 2;
  }
  else if (ch == KEY_UP)
  { 
  }
  else if(ch == KEY_DOWN)
  {
  }
  else if(ch == KEY_LEFT)
  {
  }
  else if(ch == KEY_RIGHT)
  {
  }
  else 
  {
    //insert file
    return 0;
  }

}


int main(void)
{ 
  const int width = 100;
  const int height = 40;
  if(!initscr())
  {
    perror("Init ncurses error");
    exit(EXIT_FAILURE);
  }
  initscr();
  curs_set(1);
  refresh();
  keypad(stdscr, TRUE);
  
  /*
  int offsetx=(COLS - width)/2;
  int offsety=(LINES -height)/2;
  WINDOW* win = newwin(height, width, offsety, offsetx);
  */

  FILE* fp;
  uchar* ReadBuf;
  ReadFile(fp, "./test/test.txt", &ReadBuf);
  /*
  for(u8 i=0; i<strlen(ReadBuf); i++)
    printf("%c", ReadBuf[i]);
  */
  //********************************************************************//
  //mvaddstr(0, 0, ReadBuf);
  printw(ReadBuf);
  //box(win, 0,0);
  //wrefresh(win);

  refresh();
  //getch();


  while(1)
  {
    int _task=WhatTheTask();
    if(_task==2)
    {
      break;
    }
  }
  //********************************************************************//
  free(ReadBuf);
  //delwin(win);
  endwin();  
  

  return 0;
}
