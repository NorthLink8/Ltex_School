#include "main.h"

int main(void)
{ 
  const int max_x = 4;
  const int max_y = max_x*max_x;
  
  if(!initscr())
  {
    perror("initscr:");
    exit(EXIT_FAILURE);
  }
  initscr();
  curs_set(0);
  
  for(int x=0; x< 2*max_x+1; x++)
  {
    int y = (x-max_x)*(x-max_x);
    mvaddch(max_y-y, x, 'o');
    refresh();
    sleep(1);
  }
  getch();
  endwin();
  
  return 0;
}
