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




struct OldMSG
{
	int _sockfd;
	struct sockaddr_in _cltaddr;
	unsigned int _socklen;
	unsigned char* message;
	pthread_t threadname;
};

void* echo(void* oldmsg)
{
	struct sockaddr_in clientaddr;
	unsigned char buff[255];
	socklen_t _socklen=sizeof(clientaddr);
	
	while(1)
	{
		if((recvfrom(((int)(((struct OldMSG*)oldmsg)->_sockfd)), buff, 255, 0,
						(struct sockaddr*)&clientaddr, &_socklen))<0)
		{
			perror("RECV");
			break;
		}
		unsigned char echobuff[350];
		sprintf(echobuff, "Thread: %u->Receive packet from %s:%d\nData: %s\n",
				((unsigned int)(pthread_self())),
				inet_ntoa(clientaddr.sin_addr), ntohs(clientaddr.sin_port), buff);
		printf("%s", echobuff);

		if(sendto(((int)(((struct OldMSG*)oldmsg)->_sockfd)),
					echobuff, 350,0,(struct sockaddr*)&clientaddr, _socklen)<0)
		{
			perror("SEND");
			break;
		}
		else
			perror("SEND");
	}
	close((int)((struct OldMSG*)oldmsg)->_sockfd);
}

int main(void)
{
	struct sockaddr_in servaddr, cltaddr;
	int sockfd=0;
	socklen_t socklen=sizeof(cltaddr);

	if((sockfd=socket(AF_INET, SOCK_DGRAM,0))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");

	memset(&servaddr,0,sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=8888;
	//servaddr.sin_addr.s_addr=atoi("127.0.0.1");
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");

	printf("Server addr: %s\nServer port: %d\n", 
			inet_ntoa(servaddr.sin_addr), ntohs(servaddr.sin_port));


	pthread_t servthread[5];
	for(unsigned i=0; i<5; i++)
	{
		struct OldMSG* params=(struct OldMSG*)malloc(sizeof(struct OldMSG));
		params->_sockfd=sockfd;
		params->threadname=servthread[i];
		pthread_create(&servthread[i], NULL, (void*)echo, (void*)params);
	}

	while(1)
	{
	}
	return 0;
}
