#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <stdint.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <dirent.h>
#include <ncurses.h>
#include <panel.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

pthread_t textthread;
pthread_mutex_t mut;
WINDOW* my_win[3];
unsigned endofprog=0;
sem_t semphr;

unsigned char* WGetString(unsigned int* len, WINDOW* win)
{
	*len=0;
	unsigned capacity=1;
	unsigned char* s=(unsigned char*)malloc(10*sizeof(unsigned char));
	unsigned char c=wgetch((WINDOW*)win);
	wprintw((WINDOW*)win, "%c", c);

	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(unsigned char*)realloc(s, capacity*sizeof(unsigned char));
		}
		c=wgetch((WINDOW*)win);
		wprintw((WINDOW*)win, "%c", c);
	}
	s[*len]='\0';
	return s;
}
unsigned char* GetString(unsigned int* len)
{
	*len=0;
	unsigned capacity=1;
	unsigned char* s=(unsigned char*)malloc(10*sizeof(unsigned char));
	unsigned char c=getchar();
	printf("%c", c);

	while(c!='\n')
	{
		s[(*len)++]=c;
		if(*len>=10)
		{
			capacity*=2;
			s=(unsigned char*)realloc(s, capacity*sizeof(unsigned char));
		}
		c=getchar();
		//printf("%c",c);
	}
	s[*len]='\0';
	return s;
}

struct _MSG
{
	long mtype;
	unsigned action;
	unsigned char mtext[255];
	pid_t newuserPID;
} MSG;

struct _UserMSG
{
	long mtype;
	unsigned char mtext[255];
} UserMSG;

struct _UserMSGRCV
{
	long mtype;
	unsigned char mtext[255];
} UserMSGRCV;



void* PrintMSG(void* MSGopt)
{
	while(1)
	{
		unsigned char t;
		t=wgetch(my_win[1]);
		if(/*wgetch(my_win[1])*/t=='\n')
		{
			//pthread_mutex_lock(&mut);
			sem_wait(&semphr);
			UserMSG.mtype=1L;
			key_t userkey=1010;//getpid();
			int user_msgid=msgget(userkey, 0666|IPC_CREAT);
			
			wprintw(my_win[1], "*\n");
			unsigned userlen=255;
			unsigned char* userstring=WGetString(&userlen, my_win[1]);
			sprintf(UserMSG.mtext, "%s:%s", MSG.mtext, userstring);
			if((msgsnd(user_msgid, &UserMSG, sizeof(UserMSG), 0))<0)
			{
				perror("User MSGSND");
			}
			/*
			else
			{
				perror("User MSGSND");
			}
			*/
			wrefresh(my_win[1]);
			wclear(my_win[1]);
			box(my_win[1],0,0);
			sem_post(&semphr);
			//pthread_mutex_unlock(&mut);
		}
		else if(/*wgetch(my_win[1])*/t=='\t')
		{
			UserMSG.mtype=1L;
			key_t userkey=1010;
			int user_msgid=msgget(userkey, 0666|IPC_CREAT);
			memset(MSG.mtext, 0, sizeof(MSG.mtext));
			MSG.action=0;
			MSG.newuserPID=getpid();

			MSG.action=0;
			MSG.newuserPID=0;
			key_t _mainkey=(unsigned)6666;
			int _msgid=msgget(_mainkey, 0666|IPC_CREAT);
			if(msgsnd(_msgid, &MSG, sizeof(MSG), 0)<0)
				perror("MSGSND");
			else
			{
				perror("MSGSND");
				endofprog=1;
			}
			break;
		}
	}
}


int main(void)
{
	//********************SEMAPHORE*******************//
	sem_init(&semphr, 0, 1);
	//************************************************//
	
	//******************START OF PROG*****************//
	MSG.mtype=1L;
	key_t mainkey=(unsigned)6666;
	int msgid=msgget(mainkey, 0666|IPC_CREAT);
	
	MSG.action=1;
	printf("Enter your name:");
	int namelen=255;
	unsigned char* MSGstring=GetString(&namelen);
	strcpy(MSG.mtext, MSGstring);
	MSG.newuserPID=getpid();
	//MSG.mtext=GetString(&namelen);
	if(msgsnd(msgid, &MSG, sizeof(MSG), 0)<0)
	{
		perror("MSGSND");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("MSGSND");
		printf("Press Enter key to continue\n");
		getchar();
	}
	//***********************************************//
	initscr();
	cbreak();
	noecho();
	curs_set(0);
	refresh();

	//WINDOW* my_win[3];
	my_win[0]=newwin((LINES-(LINES/4)), (COLS-(COLS/3)), 0, 0);//chat field
	box(my_win[0],0,0);
	my_win[1]=newwin((LINES/4), (COLS-(COLS/3)), (LINES-(LINES/4)), 0);//message field
	box(my_win[1],0,0);
	my_win[2]=newwin(LINES, COLS/3, 0, (COLS-(COLS/3)));//users field
	box(my_win[2],0,0);
	for(unsigned i=0; i<3; i++)
		wrefresh(my_win[i]);
	/*
	UserMSG.mtype=1L;
	key_t userkey=1010;//getpid();
	int user_msgid=msgget(userkey, 0666|IPC_CREAT);
	*/
	//pthread_t textthread;
	pthread_create(&textthread, NULL, (void*)PrintMSG, NULL);

	while(1)
	{
		/*
		if(wgetch(my_win[1])=='\n')
		{
			UserMSG.mtype=1L;
			key_t userkey=1010;//getpid();
			int user_msgid=msgget(userkey, 0666|IPC_CREAT);

			wprintw(my_win[1], "*\n");
			//Пишем сообщение
			unsigned userlen=255;
			//pthread_mutex_lock(&mut);
			unsigned char* userstring=WGetString(&userlen, my_win[1]);
			//strcpy(UserMSG.mtext, userstring);
			sprintf(UserMSG.mtext, "%s:%s", MSGstring, userstring);
			//pthread_mutex_lock(&mut);
			if((msgsnd(user_msgid, &UserMSG, sizeof(UserMSG), 0))<0)
			{
				perror("User MSGSND");
			}
			else
			{
				perror("User MSGSND");
				//wprintw(my_win[0], "%s:%s\n", MSGstring, userstring);
				//wrefresh(my_win[0]);
			}
			//pthread_mutex_unlock(&mut);
			//Сбрасываем поле
			wrefresh(my_win[1]);
			wclear(my_win[1]);
			box(my_win[1],0,0);
		}
		if(wgetch(my_win[1])=='\t')
		{
			UserMSG.mtype=1L;
			key_t userkey=1010;//getpid();
			int user_msgid=msgget(userkey, 0666|IPC_CREAT);

			memset(MSG.mtext, 0, sizeof(MSG.mtext));
			MSG.action=0;
			MSG.newuserPID=getpid();
			
			if(msgsnd(msgid, &MSG, sizeof(MSG), 0)<0)
				perror("MSGSND");
			else
				perror("MSGSND");
			
			break;
		}
		*/

		if(endofprog==1)
		{
			break;
		}

		UserMSGRCV.mtype=1L;
		key_t UserMSGRCVKey=(unsigned)getpid();
		int usermsgrcvid=msgget(UserMSGRCVKey, 0666|IPC_CREAT);
		struct msqid_ds UserRCVBuff;
		if((msgctl(usermsgrcvid, IPC_STAT, &UserRCVBuff))<0)
		{
			perror("User recv MSGCTL");
			continue;
		}
		else
		{
			if(UserRCVBuff.msg_qnum>0)
			{
				sem_wait(&semphr);
				//pthread_mutex_lock(&mut);
				if((msgrcv(usermsgrcvid, &UserMSGRCV, sizeof(UserMSGRCV), 1L, 0))<0)
				{
					perror("User MSGRCV");
					continue;
				}
				else
				{
					//perror("User MSGRCV");
					wprintw(my_win[0], "%s\n", UserMSGRCV.mtext);
					wrefresh(my_win[0]);
					//break;
				}
				
				/*
				wprintw(my_win[0], "%s\n", UserMSGRCV.mtext);
				wrefresh(my_win[0]);
				*/
				sem_post(&semphr);
				//pthread_mutex_unlock(&mut);
				//sleep(1);
			}
		}
	}
	
	//mvwprintw(my_win[0],1,1,"Hello\n");
	wrefresh(my_win[0]);
	//wgetch(my_win[1]);

	for(unsigned i=0; i<3; i++)
		delwin(my_win[i]);
	endwin();
	sem_destroy(&semphr);
}
