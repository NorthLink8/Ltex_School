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
//#include "sock.h"


unsigned char* get_string(unsigned int* len)
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
	int sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd<0)
	{
		perror("socket err");
		exit(EXIT_FAILURE);
	}
	struct hostent* hptr = gethostbyname("127.0.0.1");
	if(hptr<0)
	{
		perror("gethostbyname err");
		exit(EXIT_FAILURE);
	}
	if(hptr->h_addrtype!=AF_INET)
	{
		perror("bad address family");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=((struct in_addr*)hptr->h_addr_list[0])->s_addr;
	saddr.sin_port=htons(8888);
	if(connect(sockfd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
	{
		perror("connect err");
		exit(EXIT_FAILURE);
	}

	puts("Connect to server, about to write some stuff...");
	while(1)
	{
		//TRUE SEND
		unsigned int length=255;
		unsigned char* newstring=get_string(&length);
		if(write(sockfd, newstring, strlen(newstring))>0)
		{
			unsigned char buffer[255+1];
			memset(buffer, '\0', sizeof(buffer));
			if(read(sockfd, buffer, sizeof(buffer))>0)
				puts(buffer);
		}

	}
	puts("Client done, about to exit...");
	close(sockfd);
	return 0;
}
