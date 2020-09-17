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
	struct sockaddr_in servaddr;
	int sockfd=0, 
			socklen=sizeof(servaddr);
	unsigned char buffer[255];
	
	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("socket err");
		exit(EXIT_FAILURE);
	}
	memset(&servaddr, 0, sizeof(servaddr));
	servaddr.sin_family=AF_INET;
	servaddr.sin_port=8888;
	servaddr.sin_addr.s_addr=INADDR_ANY;

	while(1)
	{
		printf("\nEnter data to send(Type exit and press enter to exit):");
		unsigned int msglength=255;
		unsigned char* msg=get_string(&msglength);
		sprintf(buffer, "%s", msg);
		if(strcmp(buffer, "exit")==0)
			break;//exit(0);
		
		if(sendto(sockfd, buffer, 255, 0, (struct sockaddr*)&servaddr, socklen)<0)
		{
			perror("sendto err");
			exit(EXIT_FAILURE);
		}
	}
	close(sockfd);

	return 0;
}
