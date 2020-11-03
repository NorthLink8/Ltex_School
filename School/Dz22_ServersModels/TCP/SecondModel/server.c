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

int fd=0;
unsigned int clientcount=0, pawcount=0;
pthread_t tid[10];

struct InputParams
{
	unsigned int newclientfd;
};


void* paw(void* params)
{
	while(1)
	{
		/*if(pawcount<=3)
		{*/
			unsigned int pawendflag=0;
			struct sockaddr_in caddr;
			int len=sizeof(caddr);
			int newclientfd=accept(fd, (struct sockaddr*)&caddr, &len);
			if(newclientfd<0)
			{
				perror("PAW: client accept err\n");
				continue;
			}
			else
			{
				clientcount++;
				printf("PAW: success accept\n");
				if(clientcount>=10)
				{
					printf("max client connection\n");
					exit(EXIT_FAILURE);
				}
				while(1)
				{
					unsigned char buffer[255];
					memset(buffer, '\0', sizeof(buffer));
					int count=read(newclientfd, buffer, sizeof(buffer));

					unsigned char buffer2[265];
					sprintf(buffer2, "%d-> %s", newclientfd, buffer);
					if(count>0)
					{
						if(buffer[0]==' ')
						{
							close(newclientfd);
							clientcount--;
							if(pawcount>3)
							{
								pawcount--;
								pawendflag=1;
							}
							break;
						}
						buffer[0]=0xFF;
						puts(buffer2);
						write(newclientfd, buffer2, sizeof(buffer2));
					}
					if(pawendflag==1)
						break;
				}
			}
		/*}
		else
		{
			
		}*/
	}
}

int main(void)
{
	fd=socket(AF_INET, SOCK_STREAM, 0);
	if(fd<0)
	{
		perror("socket err\n");
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
	
	for(unsigned i=0; i<3; i++)
	{
		pawcount++;
		pthread_create(&tid[i], NULL, (void*)paw, NULL);
	}

	while(1)
	{
		if(clientcount>=pawcount && pawcount<10)
		{
			pawcount++;
			pthread_create(&tid[clientcount-1], NULL, (void*)paw, NULL);
		}
	}

	return 0;
}
