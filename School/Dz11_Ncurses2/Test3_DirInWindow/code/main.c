#include "main.h"
int X=0, Y=0;

void show_dir(unsigned char* path, WINDOW** win)
{
  DIR* d = opendir(path);
  if(d==NULL)
    return;
  struct dirent* dir;
  while((dir=readdir(d))!=NULL)
  {
    Y++;
    if(dir->d_type != DT_DIR)
    {
      mvwprintw(*win, Y, 1, "%s", dir->d_name);
      //printf("%s%s\n", "\x1B[32m" /*It's GREEN*/, dir->d_name);
    }
    else
    {
      if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        mvwprintw(*win, Y, 1, "%s\n", dir->d_name);
        //printf("%s%s\n", "\x1B[34m"/*It's BLUE*/, dir->d_name);
        unsigned char d_path[255];
        sprintf(d_path, "%s%s", path, dir->d_name);
        show_dir(d_path, win);
      }
      else
      {
        mvwprintw(*win, Y, 1, "%s\n", dir->d_name);
        //printf("%s%s\n", "\x1B[0m"/*NORMAL*/, dir->d_name);
      } 
    }
  }
  closedir(d);
}


int main(void)
{
  WINDOW* win;
  PANEL* panel;

  initscr();
  cbreak();
  noecho();

  win = newwin(LINES, COLS, 0, 0);
  box(win,0,0);
  mvwprintw(win, 1,1,"%s", "Hello");
  show_dir(".", &win);
  panel = new_panel(win);

  update_panels();
  doupdate();
  getch();
  endwin();
  /*
  while(1)
  {
  }
  */
  //show_dir(".", &win);
  return 0;
}
