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
#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <malloc.h>


int main(void)
{
	struct sockaddr_in snifaddr;
	int sockfd=0;
	socklen_t socklen=sizeof(snifaddr);	
	unsigned char buffer[255];

	if((sockfd=socket(AF_INET, SOCK_RAW, IPPROTO_UDP))<0)
	{
		perror("SOCK");
		exit(EXIT_FAILURE);
	}
	else
		perror("SOCK");

	/*
	memset(&snifaddr, 0, sizeof(snifaddr));
	snifaddr.sin_family=AF_INET;
	snifaddr.sin_port=8888;
	snifaddr.sin_addr.s_addr=htonl(INADDR_ANY);

	if((bind(sockfd, (struct sockaddr*)&snifaddr, sizeof(snifaddr)))<0)
	{
		perror("BIND");
		exit(EXIT_FAILURE);
	}
	else
		perror("BIND");
	*/
	while(1)
	{
	}
}
