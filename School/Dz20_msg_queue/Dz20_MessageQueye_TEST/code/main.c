#include "./main.h"

struct mesg_buffer
{
  long mesg_type;
  char mesg_text[100];
} message;

int main(int argc, char* argv[])
{
  printf("READ PROG\n");
  
  key_t key;
  int msgid=0;
  key=ftok("./progfile", 65);
  msgid=msgget(key, 0666|IPC_CREAT);
  message.mesg_type=1;
  
  printf("Write data:");
  gets(message.mesg_text);

  msgsnd(msgid, &message, sizeof(message), 0);
  printf("Data send is: %s\n", message.mesg_text);

  return 0;
}

