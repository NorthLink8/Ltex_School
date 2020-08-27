#include "../inc/browsing.h"


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

void* GetString(void* InputStr)
{
  unsigned int msg_size=255;
  unsigned char* msg_string=get_string(&msg_size, (WINDOW*)(((struct InputStruct*)InputStr)->inputwin));
  
  struct msg_buffer
  {
    long mtype;
    unsigned char mtext[255];
  } message;
  
  key_t mkey;
  int msgid=0;
  message.mtype=1L;

  for(unsigned i=1; i<=(((struct InputStruct*)InputStr)->_numofproc); i++)
  {
    mkey=100+i;
    msgid=msgget(mkey, 0666|IPC_CREAT);
    sprintf(message.mtext, "%s:%s", (((struct InputStruct*)InputStr)->_name), msg_string);
    if(msgsnd(msgid, &message, sizeof(message), 0)<0)
    {
      perror("SendFAIL");
      exit(EXIT_FAILURE);
    }
  }
  pthread_detach(pthread_self());
}


void* PrintNewMessage(/*WINDOW* win, unsigned char* _Name*/void* OutputStr)
{
  struct msg_buffer
  {
    long mtype;
    unsigned char mtext[255];
  } message;
  
  key_t mkey;
  int msgid=0;
  mkey=100+(((struct OutputStruct*)OutputStr)->_numofmyproc);
  msgid=msgget(mkey, 0666|IPC_CREAT);
  message.mtype=1L;
  if(msgrcv(msgid, &message, sizeof(message),1L,0)<0)
  {
    perror("ReadFAIL");
    exit(EXIT_FAILURE);
  }
  else
  {
    msgctl(msgid, IPC_RMID, NULL);
    wprintw((WINDOW*)(((struct OutputStruct*)OutputStr)->outputwin), "%s\n", message.mtext);
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


