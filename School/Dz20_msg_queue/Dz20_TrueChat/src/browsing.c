#include "../inc/browsing.h"

unsigned int enable=1;
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
};

pthread_mutex_t mut;

void* GetString(void* InputStr)
{
  while(1)
  {
    if(wgetch((WINDOW*)((struct InputStruct*)InputStr)->inputwin)=='\n')
    {
      enable=1;
      //exit(0);
      pthread_mutex_lock(&mut);
      struct msg_buf
      {
        long mtype;
        unsigned char mtext[255];
      } message;
      message.mtype=1L;

      unsigned int msg_len=255;
      unsigned char* msg_text=get_string(&msg_len, ((WINDOW*)((struct InputStruct*)InputStr)->inputwin));
      sprintf(message.mtext, "%s: %s\n", ((unsigned char*)((struct InputStruct*)InputStr)->_name), msg_text);

      key_t msgkey;
      int msgid=0;
      for(unsigned i=0; i<((unsigned int)((struct InputStruct*)InputStr)->_numofproc); i++)
      {
        msgkey=100+((unsigned int)((struct InputStruct*)InputStr)->_numofproc);
        msgid=msgget(msgkey, 0666|IPC_CREAT);
        if(msgsnd(msgid, &message, sizeof(message), 0)<0)
        {
          perror("msg snd string");
          exit(EXIT_FAILURE);
        }
      }
			wclear((WINDOW*)((((struct InputStruct*)InputStr)->inputwin)));
      pthread_mutex_unlock(&mut);

    }
    else if((wgetch((WINDOW*)((struct InputStruct*)InputStr)->inputwin))=='\t')
    {
			pthread_mutex_lock(&mut);
      enable=0;
			pthread_mutex_unlock(&mut);
      break;
    }
  }
	return(void*)0;
}


void* PrintNewMessage(/*WINDOW* win, unsigned char* _Name*/void* OutputStr)
{
  while(enable==1)
  {
    pthread_mutex_lock(&mut);
    struct msg_buf
    {
      long mtype;
      unsigned char mtext[255];
    } message;

    message.mtype=1L;
    key_t msgkey;
    int msgid=0;
    msgkey=100+((unsigned int)((struct OutputStruct*)OutputStr)->_numofmyproc);
    msgid=msgget(msgkey, 0666|IPC_CREAT);
    if(msgrcv(msgid, &message, sizeof(message),1L,0)<0)
    {
      perror("msg rcv print");
      exit(EXIT_FAILURE);
    }
    wprintw((WINDOW*)((WINDOW*)((struct OutputStruct*)OutputStr)->outputwin), "%s", message.mtext);
    msgctl(msgid, IPC_RMID, NULL);
    
    pthread_mutex_unlock(&mut);
    sleep(0.5);
  }
	return(void*)0;
}


void NewMassage(WINDOW* InputWin, unsigned char* _UserName, WINDOW* OutputWin, unsigned int NumOfProcess, unsigned int NumOfMyProcess)
{
  pthread_t tid;

  struct InputStruct* InputInf=(struct InputStruct*)malloc(sizeof(struct InputStruct));
  InputInf->inputwin=InputWin;
  InputInf->_name=_UserName;
  InputInf->_numofproc=NumOfProcess;

  pthread_create(&tid, NULL, (void*)GetString, (void*)InputInf);

  pthread_join(tid, NULL);
}

void PrintAllMessages(WINDOW* OutWin, unsigned int NumOfMyProc)
{
  sleep(0.3);
  pthread_t tid2;

  struct OutputStruct* OutputInf=(struct OutputStruct*)malloc(sizeof(struct OutputStruct));
  OutputInf->outputwin=OutWin;
  OutputInf->_numofmyproc=NumOfMyProc;

  pthread_create(&tid2, NULL,(void*)PrintNewMessage, (void*)OutputInf);

  //pthread_join(tid2, NULL);
}


