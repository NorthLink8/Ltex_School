#include "main.h"
u8 NLINES=0;
u8 NCOLS=0;
//int X=0, Y=0; 
u8 dY[2];
u8 ChangeWin=3;
uchar* absPath[2][PATH_MAX]; 

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color, int i);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);


void show_dir(DIR** d, uchar* path, WINDOW* win, u8* ddY)
{
  u16 count=0;
  *d=opendir(path);
  if(*d==NULL)
    return;
  
  struct dirent* dir;
  
  while((dir=readdir(*d))!=NULL)
  {
    
    if(dir->d_type == DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
    {
      count++;
      mvwprintw(win, count, 3, "%d %s", *ddY, dir->d_name);

     //uchar d_path[255];
      //sprintf(d_path, "%s%s", path, dir->d_name);
      //show_dir(d, d_path, win, ddY);
    }   
  }
  uchar name[PATH_MAX];
  if(getcwd(name, sizeof(name))!=NULL)
    mvwprintw(win, count+1, 1, "%s", name);
  mvwprintw(win, count+2, 1, "%d", *ddY);
 

  if(*ddY>count)
    *ddY=count;
  else if(*ddY<=1)
    *ddY=1;

  for(u16 i=0; i<count; i++)
     mvwprintw(win, i, 1, "%c", ' ');
  mvwprintw(win, *ddY, 1, "%c", '>');

  count=0;
  closedir(*d);
}

void new_dir(DIR** d, uchar* folder, u8 ddY)
{
  u16 count=0;
  uchar cwd[PATH_MAX];
  getcwd(cwd, sizeof(cwd));
  *d = opendir(cwd);
  if(d==NULL)
    return;
  struct dirent* dir;
    
  if(strcmp(folder, "..")!=0)
  {
    while((dir=readdir(*d))!=NULL)
    {
      if(dir->d_type==DT_DIR && strcmp(dir->d_name, ".")!=0 && strcmp(dir->d_name, "..")!=0)
      {
        count++;
        if(count==ddY)
        {         
          uchar* nfolder;
          nfolder = (uchar*)malloc(sizeof(uchar)*strlen(dir->d_name));
          strcpy(nfolder, dir->d_name);
          //chdir(nfolder);
          int dd = open(nfolder, O_RDONLY);
          fchdir(dd);
          
          /*
          uchar RealP[_POSIX_PATH_MAX];
          realpath(nfolder, RealP);
          printf("%s\n", RealP);
          */
          free(nfolder);
          count=0;
          break;
        }
      }
    }
  }
  else
  {
    chdir("..");
  }
  closedir(*d);
}


int main()
{	
  DIR* dir[2];
  WINDOW* my_wins[5];
	PANEL*  my_panels[5];
	PANEL*  top;
	int ch;

	/* Initialize curses */
	initscr();
	start_color();
	cbreak();
	noecho();
  //curs_set(0);
	keypad(stdscr, TRUE);
  

	/* Initialize all the colors */
	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	init_wins(my_wins, 5);
	
	/* Attach a panel to each window */     /* Order is bottom up */
	my_panels[0] = new_panel(my_wins[0]); 	/* Push 0, order: stdscr-0 */
	my_panels[1] = new_panel(my_wins[1]); 	/* Push 1, order: stdscr-0-1 */
	my_panels[2] = new_panel(my_wins[2]); 	/* Push 2, order: stdscr-0-1-2 */
  
  my_panels[3] = new_panel(my_wins[3]);
  my_panels[4] = new_panel(my_wins[4]);
  

	/* Set up the user pointers to the next panel */
	/*
  set_panel_userptr(my_panels[0], my_panels[1]);
	set_panel_userptr(my_panels[1], my_panels[2]);
	set_panel_userptr(my_panels[2], my_panels[0]);
  */
  set_panel_userptr(my_panels[3], my_panels[4]);
  set_panel_userptr(my_panels[4], my_panels[3]);
	/* Update the stacking order. 2nd panel will be on top */
	update_panels();

	/* Show it on the screen */
	attron(COLOR_PAIR(4));
	mvprintw(LINES - 2, 5, "Use tab to browse through the windows (Backspace to Exit)");
	attroff(COLOR_PAIR(4));
	doupdate();

	top = my_panels[3]; 

  keypad(my_wins[3], TRUE);
  keypad(my_wins[4], TRUE);
  ChangeWin=3;
  
  while((ch = getch()) != KEY_BACKSPACE)
	{	
    switch(ch)
		{	
      case '\t'://TAB
        ChangeWin++;
        if(ChangeWin>=5)
          ChangeWin=3;
        //printf("%d", ChangeWin-3);
        /*else if(ChangeWin<3)
          ChangeWin=4;*/
        //dY[ChangeWin-3]=1;

				top = (PANEL*)panel_userptr(top);
				top_panel(top);
        
        wclear(my_wins[ChangeWin]);
        show_dir(&dir[ChangeWin-3], ".", my_wins[ChangeWin], &dY[ChangeWin-3]);  
        //wrefresh(my_wins[ChangeWin]);
        
				break;
      case 'j':
        //Brows(ch, &dY[ChangeWin-3]);
        dY[ChangeWin-3]++;
        wclear(my_wins[ChangeWin]);
        show_dir(&dir[ChangeWin-3], ".", my_wins[ChangeWin], &dY[ChangeWin-3]);
        //wrefresh(my_wins[ChangeWin]);
        break;
      case 'k':
        dY[ChangeWin-3]--;
        wclear(my_wins[ChangeWin]);
        show_dir(&dir[ChangeWin-3], ".", my_wins[ChangeWin], &dY[ChangeWin-3]);
        //wrefresh(my_wins[ChangeWin]);
        break;

      case 'h':
        wclear(my_wins[ChangeWin]);
        new_dir(&dir[ChangeWin-3], "..", dY[ChangeWin-3]);
        dY[ChangeWin-3]=1;
        show_dir(&dir[ChangeWin-3], ".", my_wins[ChangeWin], &dY[ChangeWin-3]);
        //wrefresh(my_wins[ChangeWin]);       
        break;
      case 'l':
        wclear(my_wins[ChangeWin]);
        new_dir(&dir[ChangeWin-3], ".", dY[ChangeWin-3]);
        dY[ChangeWin-3]=1;
        show_dir(&dir[ChangeWin-3], ".", my_wins[ChangeWin], &dY[ChangeWin-3]);
        //wrefresh(my_wins[ChangeWin]);
        break;
		}
    
    update_panels();
		doupdate();
	}

	endwin();
	return 0;
}




/* Put all the windows */
void init_wins(WINDOW** wins, int n)
{	int x, y, i;
	char label[80];
	y = 0;
	x = 0;
	for(i = 0; i < n; ++i)
	{	
    if(i==0)
    {
      NLINES=LINES;
      NCOLS=COLS;
      y=0;
      x=0;
    }
    else if(i==1)
    {
      NLINES=LINES-7;
      NCOLS=COLS/2-5;
      y=3;
      x=5;
    }
    else if(i==2)
    {
      NLINES=LINES-7;
      NCOLS=COLS/2-10;
      y=3;
      x=COLS/2+5;
    }
    else if(i==3)
    {
      NLINES=LINES-11;
      NCOLS=COLS/2-9;
      y=6;
      x=7;
    }
    else if(i==4)
    {
      NLINES=LINES-11;
      NCOLS=COLS/2-14;
      y=6;
      x=COLS/2+7;
    }
    wins[i] = newwin(NLINES, NCOLS, y, x);
    if(i==0)
		  sprintf(label, "Main window");
    else if(i==1)
      sprintf(label, "Win1");
    else if(i==2)
      sprintf(label, "Win2");
    /*
    else if(i==3)
      sprintf(label, " ");
    else if(i==4)
      sprintf(label, " ");
    */
    win_show(wins[i], label, i + 1, i);
    /*
    y += 3;
		x += 7;
    */
	}
}

/* Show the window with a border and a label */
void win_show(WINDOW* win, char* label, int label_color, int i)
{	
  int startx, starty, height, width;

	getbegyx(win, starty, startx);
	getmaxyx(win, height, width);

  if(i>=0 && i<3)
  {
	  box(win, 0, 0);
	  mvwaddch(win, 2, 0, ACS_LTEE); 
	  mvwhline(win, 2, 1, ACS_HLINE, width - 2); 
	  mvwaddch(win, 2, width - 1, ACS_RTEE); 

	  print_in_middle(win, 1, 0, width, label, COLOR_PAIR(label_color));
  }
  else
  {
    box(win, 0, 0);
    //mvwaddch(win, 2, 0, ACS_LTEE);
    //mvwaddch(win, 2, width-1, ACS_RTEE);
  }
}

void print_in_middle(WINDOW* win, int starty, int startx, int width, char* string, chtype color)
{	
  int length, x, y;
	float temp;

	if(win == NULL)
		win = stdscr;
	getyx(win, y, x);
	if(startx != 0)
		x = startx;
	if(starty != 0)
		y = starty;
	if(width == 0)
		width = 80;

	length = strlen(string);
	temp = (width - length)/ 2;
	x = startx + (int)temp;
	wattron(win, color);
	mvwprintw(win, y, x, "%s", string);
	wattroff(win, color);
	refresh();
}
