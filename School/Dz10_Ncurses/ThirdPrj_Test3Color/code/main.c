#include "main.h"

int main(void)
{
  const u8 width = 50;
  const u8 height = 20;

  if(!initscr())
  {
    perror("initsrc:");
    exit(EXIT_FAILURE);
  }

  initscr();
  curs_set(0);
  refresh();

  int offsetx = (COLS - width)/2;
  int offsety = (LINES - height)/2;

  WINDOW* win = newwin(height, width, offsety, offsetx);
  wattron(win, A_BLINK|A_BOLD);
  

  start_color();

  uchar* hello ="Hellow, world!";
  mvaddstr(5, (COLS - strlen(hello))/2, hello);

  if(has_colors() && COLOR_PAIRS >= 13)
  {
    int n=1;

    init_pair(1,  COLOR_RED,     COLOR_BLACK);
    init_pair(2,  COLOR_GREEN,   COLOR_BLACK);
    init_pair(3,  COLOR_YELLOW,  COLOR_BLACK);
    init_pair(4,  COLOR_BLUE,    COLOR_BLACK);
    init_pair(5,  COLOR_MAGENTA, COLOR_BLACK);
    init_pair(6,  COLOR_CYAN,    COLOR_BLACK);
    init_pair(7,  COLOR_BLUE,    COLOR_WHITE);
    init_pair(8,  COLOR_WHITE,   COLOR_RED);
    init_pair(9,  COLOR_BLACK,   COLOR_GREEN);
    init_pair(10, COLOR_BLUE,    COLOR_YELLOW);
    init_pair(11, COLOR_WHITE,   COLOR_BLUE);
    init_pair(12, COLOR_WHITE,   COLOR_MAGENTA);
    init_pair(13, COLOR_BLACK,   COLOR_CYAN);
    while(n<=13)
    {
      
      color_set(n, NULL);
      mvaddstr(5+n, (COLS-strlen(hello))/2, hello);
      n++;
      
      /*
      wmove(win, (height-13)/2+n, width/2);
      waddch(win, 'Z' | COLOR_PAIR(n));
      n++;
      */
    }
  }
  box(win,0,0);
  
  getch();
  endwin();
  

  return 0;
}
