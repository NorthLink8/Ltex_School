#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <netdb.h>

unsigned char* get_string(unsigned* len)
{
	*len=0;
	unsigned capacity=1;
	unsigned char* s=(unsigned char*)malloc(10*sizeof(unsigned char));
	unsigned char c=getchar();

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


int main(int arc, char* argv[])
{
	struct sockaddr_in sendaddr;
	int sockfd=0, 
			yes=1,
			socklen=sizeof(sendaddr);
	unsigned char buffer[255];

	if((sockfd=socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");
	memset(&sendaddr, 0, sizeof(sendaddr));
	sendaddr.sin_family=AF_INET;
	sendaddr.sin_port=8888;
	sendaddr.sin_addr.s_addr=INADDR_ANY;
	if(bind(sockfd, (struct sockaddr*)&sendaddr, socklen)<0)
	{
		perror("BIND");
		//exit(EXIT_FAILURE);
	}
	else
		perror("BIND");
	if(setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int))<0)
	{
		perror("SETSOCKOPT");
		exit(EXIT_FAILURE);
	}
	else
		perror("SETSOCKOPT");



	while(1)
	{
		printf("\nEnter daat to send (Type exit and press enter to exit):");
		unsigned msglength=255;
		unsigned char* msg=get_string(&msglength);
		sprintf(buffer, "%s", msg);
		if(strcmp(buffer, "exit")==0)
			break;

		if(sendto(sockfd, buffer, 255, 0, (struct sockaddr*)&sendaddr, socklen)<0)
		{
			perror("SENDTO");
			exit(EXIT_FAILURE);
		}
		/*
		unsigned char recvbuffer[350];
		if(recvfrom(sockfd, recvbuffer, 350, 0, (struct sockaddr*)&sendaddr, &socklen)<0)
		{
			perror("RECVFROM");
			break;
		}
		else
			printf("ECHO: %s\n", recvbuffer);
			*/
	}
	close(sockfd);
	
	return 0;
}
