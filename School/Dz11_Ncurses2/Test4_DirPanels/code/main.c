#include "main.h"
u32 X=0, Y=0, dY=1;
uchar* MainFolder;/*="/home/alexandr/School";*/

void new_dir(uchar* folder)
{
  DIR* d = opendir(folder);
  if(d==NULL)
    return;
  struct dirent* dir;
  if(strcmp(folder, "..")!=0)
  {
    while((dir=readdir(d))!=NULL)
    {
      if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        Y++;
        if(dY==Y)
        {
          uchar* nfolder;
          nfolder = (uchar*)malloc(sizeof(uchar)*strlen(dir->d_name));
          strcpy(nfolder, dir->d_name);
          chdir(nfolder);
        }
      }
    }
  }
  else
  {
    chdir("..");
  }
}

void show_dir(unsigned char* path, WINDOW** win, int _dY)
{
  //wclear(*win);
  int count=0;

  DIR* d = opendir(path);
  if(d==NULL)
    return;
  struct dirent* dir;
  while((dir=readdir(d))!=NULL)
  {
//    Y++;
    
//    if(dir->d_type != DT_DIR)
//    {
//      mvwprintw(*win, Y, 1, "  %s\n", dir->d_name);
//      //printf("%s%s\n", "\x1B[32m" /*It's GREEN*/, dir->d_name);
//    }
//    else
//    {
      if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        Y++;
        mvwprintw(*win, Y, 1, "  %s\n", dir->d_name);
        //printf("%s%s\n", "\x1B[34m"/*It's BLUE*/, dir->d_name);
        unsigned char d_path[255];
        sprintf(d_path, "%s%s", path, dir->d_name);
        show_dir(d_path, win, _dY);
      }
      
//      else
//      {
//        mvwprintw(*win, Y, 1, "  %s\n", dir->d_name);
//        //printf("%s%s\n", "\x1B[0m"/*NORMAL*/, dir->d_name);
//      } 
//    }
    count++;  
  }

  if(_dY>=Y)
    _dY=Y;
  else if(_dY<1)
    _dY=1;
  
  for(u16 i=0; i<Y; i++)
    mvwprintw(*win, i, 1, "%c", ' ');
  mvwprintw(*win, _dY, 1, "%c", '>');;

  Y=0;
  closedir(d);
}



int main(void)
{
  MainFolder = (uchar*)malloc(sizeof(uchar)*strlen("/home"));
  strcpy(MainFolder, "/home");

  WINDOW* win[2];
  PANEL* panel[2];

  initscr();
  cbreak();
  curs_set(0);
  noecho();

  win[0] = newwin(LINES, COLS, 0, 0);
  box(win[0],0,0);
  win[1] = newwin(LINES-4, COLS-5, 2, 2);
  //mvwprintw(win[0], 1,1,"%s", "Hello");
  show_dir(".", &win[1], dY);
  panel[0] = new_panel(win[0]);
  panel[1] = new_panel(win[1]);
  keypad(win[1], TRUE);

  update_panels();
  doupdate();

  int ch=0;
  while((ch = wgetch(win[1]))!='q')
  {
    switch(ch)
    {
      case KEY_UP:
        dY--;
        wclear(win[1]);
        show_dir(".", &win[1], dY);
        wrefresh(win[1]);
        break;
      case KEY_DOWN:
        dY++;
        wclear(win[1]);
        show_dir(".", &win[1], dY);
        wrefresh(win[1]);
        break;

      case KEY_RIGHT:
        dY=1;
        wclear(win[1]);
        new_dir(".");
        show_dir(".", &win[1], dY);
        wrefresh(win[1]);
        break;

      case KEY_LEFT:
        dY=1;
        wclear(win[1]);
        new_dir("..");
        show_dir(".", &win[1], dY);
        wrefresh(win[1]);
        break;
    }
  }
  //getch();
  endwin();
  //show_dir(".", &win);
  return 0;
}
