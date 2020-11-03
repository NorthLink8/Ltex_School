#include "./main.h"


WINDOW* my_wins[7];
PANEL* my_panels[7];
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
  init_wins(my_wins,7);
  my_panels[0]=new_panel(my_wins[0]);
  my_panels[1]=new_panel(my_wins[1]);
  my_panels[2]=new_panel(my_wins[2]);
  my_panels[3]=new_panel(my_wins[3]);
  my_panels[4]=new_panel(my_wins[4]);
  my_panels[5]=new_panel(my_wins[5]);
  my_panels[6]=new_panel(my_wins[6]);

  set_panel_userptr(my_panels[4], my_panels[5]);
  set_panel_userptr(my_panels[5], my_panels[4]);
  
  update_panels();
  attron(COLOR_PAIR(4));
  mvprintw(LINES-2,5,"Use tab to browse through the windows (2xTAB to Exit)\n");
  attroff(COLOR_PAIR(4));
  doupdate();
  top=my_panels[4];
  ChangeWin=3;
}

struct _NumOfProc
{
  long mtype;
  unsigned int num;  
} NumOfProc;

unsigned int ProcNum=0;


struct InputStruct
{
  unsigned char* _name;
  WINDOW* inputwin;
  unsigned int _numofproc;
};
struct OutputStruct
{
  WINDOW* outputwin;
  unsigned int _numofmyproc;
} OutputStruct;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////
unsigned int enable=1, _end=0;
pthread_mutex_t mut;



void* GetString(void* InputStr)
{
	struct msg_buf
	{
		long mtype;
    unsigned char mtext[255];
  } message;
	message.mtype=1L;

	while(1)
	{
		if(wgetch((WINDOW*)(((struct InputStruct*)InputStr)->inputwin))=='\n')
		{
			pthread_mutex_lock(&mut);
			wprintw((WINDOW*)(((struct InputStruct*)InputStr)->inputwin), "->");
			unsigned int msg_len=255;
			unsigned char* msg_text=get_string(&msg_len, ((WINDOW*)((struct InputStruct*)InputStr)->inputwin));
			sprintf(message.mtext, "%s: %s\n", ((unsigned char*)((struct InputStruct*)InputStr)->_name), (unsigned char*)msg_text);
			wrefresh((WINDOW*)(((struct InputStruct*)InputStr)->inputwin));
			wclear((WINDOW*)(((struct InputStruct*)InputStr)->inputwin));

			key_t msgkey;
      int msgid=0;
			msgkey=ftok("./progfile", 0);
			msgid=msgget(msgkey, 0666|IPC_CREAT);
			if(msgrcv(msgid, &NumOfProc, sizeof(NumOfProc),1L,0)<0)
			{
				perror("NewRCV for send");
				exit(EXIT_FAILURE);
			}
			unsigned int numofmessages=NumOfProc.num;
			if(msgsnd(msgid, &NumOfProc, sizeof(NumOfProc),0)<0)
			{
				perror("NewSND for send");
				exit(EXIT_FAILURE);
			}

			//Нужно прочитать сколько у нас всего процессов запуенно на данный момент
			//После чего отправить сообщение на каждый процесс
		
      for(unsigned i=1; i<=numofmessages; i++)
      {
        msgkey=100+i;
        msgid=msgget(msgkey, 0666|IPC_CREAT);
        if(msgsnd(msgid, &message, sizeof(message), 0)<0)
        {
          perror("msg snd string");
          exit(EXIT_FAILURE);
        }
      }
			pthread_mutex_unlock(&mut);
		}
		else if(wgetch((WINDOW*)(((struct InputStruct*)InputStr)->inputwin))=='\t')
		{
			pthread_mutex_lock(&mut);
			_end=1;
			pthread_mutex_unlock(&mut);
		}
	}
  return(void*)0;
}


void* PrintNewMessage(void* OutputStr)
{
	unsigned int printline=0;
	struct msg_buf
	{
		long mtype;
		unsigned char mtext[255];
	} message;
	message.mtype=1L;
	key_t _readkey;
	int _readid;
	_readkey=100+((unsigned int)(((struct OutputStruct*)OutputStr)->_numofmyproc));
	_readid=msgget(_readkey, 0660|IPC_CREAT);
	struct msqid_ds readbuf;
	if(msgrcv(_readid, &message, sizeof(message), 1L, 0)<0)
	{
		perror("read msg error");
		exit(EXIT_FAILURE);
	}
	
	int t=0;
	while(_end==0)
	{
		pthread_mutex_lock(&mut);	
		if(msgctl(_readid, IPC_STAT, &readbuf)<0)
		{
			perror("CTLcheck failed");
			exit(EXIT_FAILURE);
		}
		//unsigned int numofmsg=readbuf.msg_cbytes;
		
		if ((unsigned int)readbuf.msg_qnum>0)
		{
			if(msgrcv(_readid, &message, sizeof(message), 1L, 0)<0)
			{
				perror("read msg error");
				exit(EXIT_FAILURE);
			}
			wrefresh((WINDOW*)(((struct OutputStruct*)OutputStr)->outputwin));
			wprintw((WINDOW*)(((struct OutputStruct*)OutputStr)->outputwin), "%s", message.mtext);
			readbuf.msg_qnum--;
			//wrefresh((WINDOW*)(((struct OutputStruct*)OutputStr)->outputwin));
		}
		
		printline++;
		if(printline>=LINES-11)
		{
			printline=0;
			wclear((WINDOW*)(((struct OutputStruct*)OutputStr)->outputwin));
		}
		pthread_mutex_unlock(&mut);
		//sleep(1);
	}
	return(void*)0;
}



int main(void)
{
  NumOfProc.mtype=1L;
  key_t _key;
  int _msgid=0;
  _key=ftok("./progfile",0);
  _msgid=msgget(_key, 0666|IPC_CREAT);
  struct msqid_ds buf;
  int rc=msgctl(_msgid, IPC_STAT, &buf);
  int num_messages=buf.msg_cbytes;

  //NumOfProc.num=0;
  printf("messages queue: %d\n", num_messages);
  if(num_messages>0)
  {
    if(msgrcv(_msgid, &NumOfProc, sizeof(NumOfProc),1L,0)<0)
    {
      perror("msgrcv first");
      exit(EXIT_FAILURE);
    }
    NumOfProc.num++;
    ProcNum=NumOfProc.num;
    if(msgsnd(_msgid, &NumOfProc, sizeof(NumOfProc),0)<0)
    {
			perror("msgsnd1 first");
      exit(EXIT_FAILURE);
    }
  }
  else
  {
    NumOfProc.num=1;
    ProcNum=NumOfProc.num;
    if(msgsnd(_msgid, &NumOfProc, sizeof(NumOfProc),0)<0)
    {
      perror("msgsnd2");
      exit(EXIT_FAILURE);
    }
  }
  
  printf("Your %d in room\n", ProcNum);
  //return 0;
  //  WINDOW* my_wins[5];
  //  PANEL* my_panels[5];
  //  PANEL* top;
  int ch=0;
  unsigned int namelength=50;
  unsigned char* UserName;
  printf("Enter your name:");
  UserName=get_simString(&namelength);
  
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
  init_pair(5,  COLOR_RED,    COLOR_BLACK);
  init_pair(6,  COLOR_GREEN,  COLOR_BLACK);
  ChangeWin=3;
  ManagerInit();
  attron(COLOR_PAIR(1));
  mvprintw(LINES-3,5,"User name:%s\n", UserName);
  attroff(COLOR_PAIR(1));
  wrefresh(my_wins[4]);
  wrefresh(my_wins[5]);
  wrefresh(my_wins[6]);


  //PrintAllMessages(my_wins[5], ProcNum);



  struct InputStruct* InputInf=(struct InputStruct*)malloc(sizeof(struct InputStruct));
  InputInf->inputwin=my_wins[ChangeWin+1];
  InputInf->_name=UserName;
  InputInf->_numofproc=NumOfProc.num;
  struct OutputStruct* OutputInf=(struct OutputStruct*)malloc(sizeof(struct OutputStruct));
  OutputInf->outputwin=my_wins[5];
  OutputInf->_numofmyproc=ProcNum;

  pthread_t mtid[2];
  pthread_create(&mtid[0], NULL, (void*)GetString, (void*)InputInf);
  pthread_create(&mtid[1], NULL, (void*)PrintNewMessage, (void*)OutputInf);
  
  //pthread_join(mtid[0], NULL);
  //pthread_join(mtid[1], NULL);
  //Обработка потоков
  
  while(1)
  {
		if(_end==0)
		{
			/*
			wrefresh(my_wins[5]);
			sleep(0.5);
			*/
			//pthread_join(mtid[0], NULL);
			//pthread_join(mtid[1], NULL);
			continue;
		}
		else
		{
			break;
		}
		
  }
  
  endwin();

  if(msgrcv(_msgid, &NumOfProc, sizeof(NumOfProc), 1L, 0)<0)
  {
    perror("End msg receive");
    exit(EXIT_FAILURE);
  }
  if(NumOfProc.num<=1)
  {
    NumOfProc.num=0;
    msgctl(_msgid, IPC_RMID, NULL);
  }
  else
    NumOfProc.num--;
  printf("Num of users in room: %d\n", NumOfProc.num);
  if(msgsnd(_msgid, &NumOfProc, sizeof(NumOfProc), 0)<0)
  {
    perror("End msg send");
    exit(EXIT_FAILURE);
  }
  
  return 0;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Put all the windows */
void init_wins(WINDOW** wins, int n)
{	
  int x, y, i;
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
      NCOLS=COLS/3-5;
      y=3;
      x=5;
    }
    else if(i==2)
    {
      NLINES=LINES-7;
      NCOLS=COLS/3-5;
      y=3;
      x=COLS/3+5;
    }
    else if(i==3)
    {
      NLINES=LINES-7;
      NCOLS=COLS/3-5;
      y=3;
      x=COLS-60;
    }
    

    else if(i==4)
    {
      NLINES=LINES-11;
      NCOLS=COLS/3-9;
      y=6;
      x=7;
    }
    else if(i==5)
    {
      NLINES=LINES-11;
      NCOLS=COLS/3-9;
      y=6;
      x=COLS/3+7;
    }
    else if(i==6)
    {
      NLINES=LINES-11;
      NCOLS=COLS/3-9;
      y=6;
      x=COLS-58;
    }
    wins[i] = newwin(NLINES, NCOLS, y, x);
    if(i==0)
		  sprintf(label, "CHAT ROOM");
    else if(i==1)
      sprintf(label, "MESSAGE");
    else if(i==2)
      sprintf(label, "CHAT");
    else if(i==3)
      sprintf(label, "USERS");
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

  if(i>=0 && i<4)
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
