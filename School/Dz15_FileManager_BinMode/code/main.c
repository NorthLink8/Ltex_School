#include "./main.h"

WINDOW* my_wins[5];
PANEL* my_panels[5];
PANEL* top;

uint8_t NLINES=0;
uint8_t NCOLS=0;
uint8_t dY[2];
uint8_t ChangeWin=3;
//unsigned char absPath[2][PATH_MAX]; 

void init_wins(WINDOW **wins, int n);
void win_show(WINDOW *win, char *label, int label_color, int i);
void print_in_middle(WINDOW *win, int starty, int startx, int width, char *string, chtype color);

void ManagerInit()
{
  init_wins(my_wins,5);
  my_panels[0]=new_panel(my_wins[0]);
  my_panels[1]=new_panel(my_wins[1]);
  my_panels[2]=new_panel(my_wins[2]);
  my_panels[3]=new_panel(my_wins[3]);
  my_panels[4]=new_panel(my_wins[4]);

  set_panel_userptr(my_panels[3], my_panels[4]);
  set_panel_userptr(my_panels[4], my_panels[3]);
  update_panels();
  attron(COLOR_PAIR(4));
  mvprintw(LINES-2,5,"Use tab to browse through the windows (Backspace to Exit)");
  attroff(COLOR_PAIR(4));
  doupdate();
  top=my_panels[3];
  ChangeWin=3;
}


int main(void)
{
  unsigned char absPath[2][PATH_MAX];
  strcpy(absPath[0], "/home/alexandr");
  strcpy(absPath[1], "/home/alexandr");
  
//  WINDOW* my_wins[5];
//  PANEL* my_panels[5];
//  PANEL* top;
  int ch=0;
  
  initscr();
  start_color();
  cbreak();
  noecho();
  curs_set(0);
  keypad(stdscr, TRUE);

  init_pair(1,  COLOR_RED,    COLOR_BLACK);
  init_pair(2,  COLOR_GREEN,  COLOR_BLACK);
  init_pair(3,  COLOR_BLUE,   COLOR_BLACK);
  init_pair(4,  COLOR_CYAN,   COLOR_BLACK);

  /*
  init_wins(my_wins,5);
  my_panels[0]=new_panel(my_wins[0]);
  my_panels[1]=new_panel(my_wins[1]);
  my_panels[2]=new_panel(my_wins[2]);
  my_panels[3]=new_panel(my_wins[3]);
  my_panels[4]=new_panel(my_wins[4]);

  set_panel_userptr(my_panels[3], my_panels[4]);
  set_panel_userptr(my_panels[4], my_panels[3]);
  update_panels();
  attron(COLOR_PAIR(4));
  mvprintw(LINES-2,5,"Use tab to browse through the windows (Backspace to Exit)");
  attroff(COLOR_PAIR(4));
  doupdate();
  top=my_panels[3];
  ChangeWin=3;
  */
  ManagerInit();
  //show_dir(absPath[0], my_wins[3], &dY[0]);
  //show_dir(absPath[1], my_wins[4], &dY[1]);
  chdir(absPath[0]);
  
  while((ch=getch())!=KEY_BACKSPACE)
  {
    switch(ch)
    {
      case '\t':
        ChangeWin++;
        if(ChangeWin>=5)
          ChangeWin=3;

        top=(PANEL*)panel_userptr(top);
        top_panel(top);
        wclear(my_wins[ChangeWin]);
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        wrefresh(my_wins[ChangeWin]);
        break;

      case 'j':
        dY[ChangeWin-3]++;
        wclear(my_wins[ChangeWin]);
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        break;
      case 'k':
        dY[ChangeWin-3]--;
        wclear(my_wins[ChangeWin]);
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        break;

      case 'h':
        wclear(my_wins[ChangeWin]);
        new_dir(absPath[ChangeWin-3], "..", dY[ChangeWin-3]);
        dY[ChangeWin-3]=1;
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        break;
      case 'l':
        wclear(my_wins[ChangeWin]);
        new_dir(absPath[ChangeWin-3], ".", dY[ChangeWin-3]);
        dY[ChangeWin-3]=1;
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        break;
      case '\n':
        wclear(my_wins[ChangeWin]);
        wrefresh(my_wins[ChangeWin-3]);
        run_prog(my_wins[ChangeWin], absPath[ChangeWin-3], dY[ChangeWin-3]);
        ManagerInit();
        show_dir(absPath[ChangeWin-3], my_wins[ChangeWin], &dY[ChangeWin-3]);
        break;
    }
    update_panels();
    doupdate();
  }
  endwin();
  return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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
    //box(win, 0, 0);
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
