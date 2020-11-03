#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <netdb.h>
#include <malloc.h>
//SENDER

unsigned char* getstring(unsigned int* len)
{
	*len=0;
	unsigned int capacity=1;
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

int main(void)
{
	struct sockaddr_in sendaddr;
	int sockfd=0,
			sendaddrlen=sizeof(sendaddr);
	unsigned char buffer[255];

	if(socket(AF_INET, SOCK_DGRAM, 0)<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");

	memset(&sendaddr, 0, sizeof(sendaddr));
	sendaddr.sin_family=AF_INET;
	sendaddr.sin_port=8888;
	sendaddr.sin_addr.s_addr=inet_addr("239.0.0.1");
	//sendaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	/*
	if(bind(sockfd, (struct sockaddr*)&sendaddr, sizeof(sendaddr))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");
	*/
	
	while(1)
	{
		printf("Enter your message:\n");
		int strlen=80;
		unsigned char* string=getstring(&strlen);
		strcpy(string, buffer);

		if(sendto(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&sendaddr, sendaddrlen))
		{
			perror("SENDTO");
		}
		else
			perror("SENDTO");
	}
}
