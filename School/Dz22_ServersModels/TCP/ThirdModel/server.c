#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>


unsigned int pawcount=0, clientcount=0;
pthread_t tid[10];
pthread_mutex_t mut;

struct CltApplication
{
	long mtype;
	int _clientfd;
};

void* paw(void* params)
{
	//Тут поток читает сообщение из очереди, если там такое имеется. 
	//Берет от туда fd нового клиента и подключается к нему для дальнейшей работы
	struct CltApplication postApp;
	postApp.mtype=1L;
	while(1)
	{
		key_t key;
		int msgid=0;
		key=1000;//ftok("./programmfile",0);
		msgid=msgget(key, 0666|IPC_CREAT);
		struct msqid_ds buff;
		int rc=msgctl(msgid, IPC_STAT, &buff);
		int numofmsg=buff.msg_qnum;
		if(numofmsg>0)
		{
			if(msgrcv(msgid, (void*)&postApp, sizeof(postApp), 1L, 0/*IPC_NOWAIT*/)<0)
			{
				perror("MSGRCV");
				continue;
			}
			else
			{
				perror("MSGRCV");
				while(1)
				{
					unsigned char buffer[255];
					memset(buffer, 0, sizeof(buffer));
					if(read(postApp._clientfd, buffer, sizeof(buffer))>0)
					{
						if((strcmp(buffer, "exit")==0))
						{
							close(postApp._clientfd);
							clientcount--;
							if(pawcount>3)
								pawcount--;
							break;
						}
						unsigned char buffer2[300];
						sprintf(buffer2, "%d-> %s", postApp._clientfd, buffer);
						write(postApp._clientfd, buffer2, sizeof(buffer2));
						printf("%s\n", buffer2);
					}
				}
			}
		}
	}
}


//*******************************************************************************//
int main(void)
{
	int fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(8888);

	if(bind(fd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");
	
	if(listen(fd, 10)<0)
	{
		perror("MAX CONNECT");
		exit(EXIT_FAILURE);
	}
	
	fprintf(stderr, "Listen on part %i for client...\n", 8888);

	//*****************************************************************************************//
	
	for(unsigned i=0; i<3; i++)
	{
		pawcount++;
		pthread_create(&tid[i], NULL, (void*)paw, NULL);
	}
	
	while(1)
	{
		struct sockaddr_in caddr;
		int len=sizeof(caddr);
		int newclientfd=accept(fd, (struct sockaddr*)&caddr, &len);
		if(newclientfd<0)
		{
			perror("ACCEPT");
			continue;
		}
		else
		{
			clientcount++;
			perror("ACCEPT");
			//Вот тут надо создавать очередь из заявок
			struct CltApplication firstApp;
			//firstApp=(struct CltApplication*)malloc(sizeof(struct CltApplication));
			firstApp.mtype=1L;
			firstApp._clientfd=newclientfd;
			
			key_t key;
			int msgid=0;
			key=1000;//ftok("./programmfile",0);
			msgid=msgget(key, 0666|IPC_CREAT);
			if(msgsnd(msgid, (void*)&firstApp, sizeof(firstApp),0)<0)
			{
				perror("MSGSND");
				clientcount--;
				//Тут надо оборвать соединение, чтобы клиент переподключился заново.
				//Или переподключить его самому
				close(newclientfd);
				continue;
			}
		}
		
		if(clientcount>=pawcount && pawcount<10)
		{
			pawcount++;
			pthread_create(&tid[clientcount-1], NULL, (void*)paw, NULL);
		}
		
	}
}
