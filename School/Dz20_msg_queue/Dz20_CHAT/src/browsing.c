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

pthread_mutex_t mut;


void NewMassage(WINDOW* InputWin, unsigned char* _UserName, WINDOW* OutputWin, unsigned int NumOfProcess, unsigned int NumOfMyProcess)
{
  pthread_t tid;

  struct InputStruct* InputInf=(struct InputStruct*)malloc(sizeof(struct InputStruct));
  InputInf->inputwin=InputWin;
  InputInf->_name=_UserName;
  InputInf->_numofproc=NumOfProcess;

  //pthread_create(&tid, NULL, (void*)GetString, (void*)InputInf);

  //pthread_join(tid, NULL);
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


