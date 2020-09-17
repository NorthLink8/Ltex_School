#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>


int main(/*int argc, unsigned char* argv[]*/void)
{
	int fd=socket(AF_INET, SOCK_STREAM,0);
	if(fd<0)
	{
		perror("socket err");
		exit(EXIT_FAILURE);
	}

	struct sockaddr_in saddr;
	memset(&saddr, 0, sizeof(saddr));
	saddr.sin_family=AF_INET;
	saddr.sin_addr.s_addr=htonl(INADDR_ANY)/*inet_addr("192.168.100.20")*/;
	saddr.sin_port=htons(8888);

	if(bind(fd, (struct sockaddr*)&saddr, sizeof(saddr))<0)
	{
		perror("bind err");
		exit(EXIT_FAILURE);
	}
	if(listen(fd, 10)<0)
	{
		perror("max connections err");
		exit(EXIT_FAILURE);
	}
	fprintf(stderr, "Listen on port %i for client..\n", 888);
	
	while(1)
	{
		struct sockaddr_in caddr;
		int len=sizeof(caddr);

		int client_fd = accept(fd, (struct sockaddr*)&caddr, &len);
		if(client_fd<0)
		{
			perror("accept err");
			continue;
		}
	

		for(unsigned i=0; i<255; i++)
		{
			unsigned char buffer[1025];
			memset(buffer, '\0', sizeof(buffer));
			int count=read(client_fd, buffer, sizeof(buffer));
			if(count>0)
			{
				buffer[0]=0xFF;
				puts(buffer);
				write(client_fd, buffer, sizeof(buffer));
			}
		}
		close(client_fd);
	}
	return 0;
}
