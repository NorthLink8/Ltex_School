#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <pthread.h>
#include <dirent.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <sys/syscall.h>
#include <sys/ipc.h>
#include <sys/msg.h>

pthread_t serverthread;
pthread_t clientthread;

void* _server(void* servparams)
{
}
void* _client(void* cltparams)
{
}

unsigned char* getstring(unsigned int* len)
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
	}
	s[*len]='\0';
	return s;
}
struct _MSG
{
	long mtype;
	unsigned UserNum;
} MSG;

int main(void)
{
	/*
	 * Небольшая щаглушка для упроения выбора работы приложения.
	 * Например: сервер это будет или клиент для P2P работы
	 **********************************************************************/
	//Вопросы:
	//1) Как будет происходить выбор модели работы приложения:
	//	1.1) ЛИбо перед пользователем изначально встает выбор, кем он хочет изначально быть
	//	1.2) Либо приложение само решает, кем в данный момент является запущенное приложение: 
	//	клиентом или сервером
	MSG.mtype=1L;
	key_t AppMode=(unsigned)1998;
	int msgid=0;
	if((msgid=msgget(AppMode, 066|IPC_CREAT))<0)
	{
		perror("MSGGET");
		exit(EXIT_FAILURE);
	}
	else
		perror("MSGGET");

	struct msqid_ds ModeBuff;
	int rc=0;
	if((rc=msgctl(msgid, IPC_STAT, &ModeBuff))<0)
	{
		perror("MSGCTL");
		exit(EXIT_FAILURE);
	}
	else
		perror("MSGCTL");
	

	pthread_t AppThread;
	if((unsigned)ModeBuff.msg_qnum>0)
	{
		//Это КЛИЕНТ
	}
	else
	{
		//Это СЕРВЕР
		
	}
	//********************************************************************//
	while(1)
	{
	}
}
