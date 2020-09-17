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


int main(void)
{
	struct sockaddr_in servaddr, cltaddr;
	int sockfd=0;
	socklen_t socklen=sizeof(cltaddr);
	unsigned char buffer[255];

	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("sock err");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK:");
	
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=8888;
	servaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&servaddr, sizeof(servaddr))<0)
	{
		perror("bind err");
		exit(EXIT_FAILURE);
	}
	else
	{
		perror("BIND:");
	}


	while(1)
	{
		if(recvfrom(sockfd, buffer, 255, 0, (struct sockaddr*)&cltaddr, &socklen)<0)
		{
			perror("recv err");
			continue;
		}
		printf("Receive packet from %s:%d\nData: %s\n\n",
				inet_ntoa(cltaddr.sin_addr), ntohs(cltaddr.sin_port), buffer);
	}
	close(sockfd);


	return 0;
}
