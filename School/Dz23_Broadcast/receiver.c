#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(void)
{
	struct sockaddr_in recvaddr;
	int sockfd=0;

	if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");
	memset(&recvaddr, 0, sizeof(recvaddr));
	recvaddr.sin_family=AF_INET;
	recvaddr.sin_port=8888;
	recvaddr.sin_addr.s_addr=atoi("127.0.0.1");
	//recvaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if(bind(sockfd, (struct sockaddr*)&recvaddr, sizeof(recvaddr))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");

	unsigned sinlen=sizeof(recvaddr);
	if(getsockname(sockfd, (struct sockaddr*)&recvaddr, &sinlen/*sizeof(recvaddr)*/)<0)
	{
		perror("GETSOCKNAME");
		exit(EXIT_FAILURE);
	}
	else
		perror("GETSOCKNAME");
	

	//unsigned char* _sockAddr=(unsigned char*)malloc(strcpy(htons(INADDR_ANY))*sizeof(unsigned char));




	while(1)
	{
		unsigned char buffer[350];
		memset(buffer, 0, strlen(buffer));
		if(recvfrom(sockfd, buffer, strlen(buffer), 0, (struct sockaddr*)&recvaddr, &sinlen)<0)
			perror("RECVFROM");
		else
		{
			perror("RECVFROM");
			printf("%s\n", buffer);
		}
	}
	shutdown(sockfd, 2);


	return 0;
}
