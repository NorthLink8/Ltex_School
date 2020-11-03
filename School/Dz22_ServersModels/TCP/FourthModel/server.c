#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <malloc.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
//#include <netdb.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/msg.h>
#include <sys/ipc.h>
#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/epoll.h>

int main(void)
{
	struct epoll_event event, events[5];
	int epollfd=epoll_create1(0);//создали мультиплексор
	unsigned int running=1, event_count=0;
	size_t bytes_read;
	char read_buffer[256];

	if(epollfd<0)
	{
		perror("EPOLL CREATE");
		exit(EXIT_FAILURE);
	}

	event.events=EPOLLIN;
	event.data.fd=0;
	if(epoll_ctl(epollfd, EPOLL_CTL_ADD, 0, &event))//добавлии дескриптор ввода вывода
	{
		fprintf(stderr, "Failed to add file descriptior to epoll\n");
		close(epollfd);
	}
	
	
	while(running)
	{
		printf("\nPolling for input...\n");
		event_count=epoll_wait(epollfd, events, 5, 30000);
		printf("%d read events\n", event_count);

		for(unsigned i=0; i<event_count; i++)
		{
			printf("Reading file descriptor '%d' -- ", events[i].data.fd);
			bytes_read=read(events[i].data.fd, read_buffer, 255);
			printf("%zd bytes read.\n", bytes_read);
			read_buffer[bytes_read]='\0';
			printf("Read '%s' \n", read_buffer);

			if(!strcmp(read_buffer, "stop\n"))
				running=0;
		}
	}
	
	
	if(close(epollfd))
	{
		perror("EPOLL CLOSE");
		exit(EXIT_FAILURE);
	}
	return 0;
}
