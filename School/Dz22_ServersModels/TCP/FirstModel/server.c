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
#include <errno.h>
#include <pthread.h>
#include <dirent.h>


struct InputParams
{
	int newclientfd;
};

void* _function(void* params)
{
	while(1)
	{
		unsigned char buffer[255];
		memset(buffer, '\0', sizeof(buffer));
		int count=read(((int)(((struct InputParams*)params)->newclientfd)), buffer, sizeof(buffer));
		
		unsigned char buffer2[300];
		sprintf(buffer2, "%d%s", ((int)(((struct InputParams*)params)->newclientfd)), buffer);
		if(count>0)
		{
			
			if(buffer[0]==' ')
			{
				close((int)(((struct InputParams*)params)->newclientfd));
				break;
			}
			buffer[0]=0xFF;
			puts(buffer2);
			write(((int)(((struct InputParams*)params)->newclientfd)), buffer2, sizeof(buffer2));
		}
	}
}


int main(void)
{
	int fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0)
	{
		perror("socket err");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=htonl(INADDR_ANY);
	saddr.sin_port=htons(8888);

	if(bind(fd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
	{
		perror("bind err");
		exit(EXIT_FAILURE);
	}
	if(listen(fd, 10)<0)
	{
		perror("max connection err");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Listen on part %i for client...\n", 8888);
	
	pthread_t tid[10];//Максимальное колличество подключений
	unsigned int clientcount=0;

	while(1)
	{
		struct sockaddr_in caddr;
		int len=sizeof(caddr);
		printf("check prog run point 1");
		int client_fd=accept(fd, (struct sockaddr*)&caddr, &len);
		printf("check prog run point 2");
		if(client_fd<0)
		{
			perror("client accept err");
			continue;
		}
		else
		{
			clientcount++;
			if(clientcount>=10)
			{
				printf("Max client count");
				exit(EXIT_FAILURE);
			}
			struct InputParams* _InputParams=(struct InputParams*)malloc(sizeof(struct InputParams));
			_InputParams->newclientfd=client_fd;
			pthread_create(&tid[clientcount], NULL, (void*)_function, (void*)_InputParams);
		}
			
	}
	return 0;
}
