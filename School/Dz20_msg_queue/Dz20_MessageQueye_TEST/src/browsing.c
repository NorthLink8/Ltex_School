#include "../inc/browsing.h"


void* GetString(void* window)
{
  //exit(1);
  unsigned int mass=50;
  unsigned char* _string=get_string(&mass, (WINDOW*)window);
  //wprintw((WINDOW*)window, "%s\n", _string);
  return(void*)0;
}

typedef struct msbuf
{
  long mtype;
  unsigned char mtext[255];
} message_buf;

void NewMassage(WINDOW* win/*, unsigned int UserNum*/ )
{
  pthread_t tid;
  /*
  key_t _key;
  message_buf _sbuf;
  size_t buf_length;
  int msg_id;

  _key=ftok("prof", 65);//creat unique key
  msg_id=msgget(_key, 0666|IPC_CREAT);
  _sbuf.mtype=1;
  fgets(_sbuf.mtext, 255, stdin);
  msgsnd(msg_id, &_sbuf, sizeof(_sbuf), 0);//send message
  */

  struct KeyStr
  {
    key_t* key;
    unsigned char text[255];
    size_t text_length;
    int m_id;
  };
  

  pthread_create(&tid, NULL, (void*)GetString, (void*)win);
  pthread_join(tid, NULL);
}



