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

  uchar* hello="Hello world!";

  mvaddstr(LINES/2, (COLS-strlen(hello))/2, hello);
  box(win, 0, 0);

  wrefresh(win);
  getch();

  delwin(win);
  endwin();

  return 0;
}
