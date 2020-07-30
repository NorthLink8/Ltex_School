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
  //box(win,0,0);
 
  //int ch = getch();
  //Есть еще cbreak(); Который считывает данные с клавиатуры посимвольно. Игрулю можно написать
  //keypad(stdstr, TRUE); //Позволяет обработать нажатия специальных клавищ. Ctrl, Delete и так далее
  
  int ch=0;
  nodelay(stdscr, TRUE);
  for(;;)
  {
    if((ch == getch())==ERR)
    {
      //пользователь не отвечает
    }
    else
    {
      //Пользователь нажал клавишу
    }
  }
  
  getch();
  endwin();
  

  return 0;
}
