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
//RECEIVER


int main(void)
{
	struct sockaddr_in recvaddr;
	int sockfd=0,
			recvaddrlen=sizeof(recvaddr);
	unsigned char buffer[255];

	if((sockfd=socket(AF_INET, SOCK_DGRAM, 0))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");

	/*
	const int optval=1;
	if(setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval))<0)
	{
		perror("SETSOCKOPT");
		exit(EXIT_FAILURE);
	}
	else
		perror("SETSOCKOPT");
	*/
	
	memset(&recvaddr, 0, sizeof(recvaddr));
	recvaddr.sin_family=AF_INET;
	recvaddr.sin_port=8888;
	recvaddr.sin_addr.s_addr=htonl(INADDR_ANY);
	
	if(bind(sockfd, (struct sockaddr*)&recvaddr, sizeof(recvaddr))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");

	struct ip_mreq imr;
	imr.imr_multiaddr.s_addr=inet_addr("239.0.0.1");
	imr.imr_interface.s_addr=htonl(INADDR_ANY);
	if(setsockopt(sockfd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &imr, sizeof(imr))<0)
	{
		perror("SETSOCKOPT");
		exit(EXIT_FAILURE);
	}
	else
		perror("SETSOCKOPT");

	int cnt=0;
	while(1)
	{
		if(recvfrom(sockfd, buffer, sizeof(buffer), 0, (struct sockaddr*)&recvaddr, &recvaddrlen)<0)
		{
			perror("RECVFROM");
			//exit(EXIT_FAILURE);
		}
		else
			perror("RECVFROM");
		
	}


	return 0;
}
