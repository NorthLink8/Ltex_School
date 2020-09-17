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


int main(int argc, char* argv[])
{
	int listenfd=0, connfd=0;
	struct sockaddr_in serv_addr;

	char sendBuff[1024];
	time_t ticks;

	listenfd=socket(AF_INET, SOCK_STREAM, 0);//натсраиваем неименованный сокет INET-inet, STREAM_TCP, 0- automaticall change mode.
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(sendBuff, '0', sizeof(sendBuff));

	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(5000);

	bind(listenfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));//Создает сокет из структуры
	listen(listenfd, 10);//10-максимальное число подключений. Первым параметром передается дискриптор сокета, который надо прослушать

	while(1)
	{
		connfd=accept(listenfd, (struct sockaddr*)NULL, NULL);//Ожидаем входящее соединение, возвращается дискриптор сокета при подключении
		ticks=time(NULL);
		snprintf(sendBuff, sizeof(sendBuff), "%.24s\r\n", ctime(&ticks));//Вписываем время в передаваемый буфер. Как только произошло подключение
		write(connfd, sendBuff, strlen(sendBuff));//пишем в сокет
		close(connfd);//закрываем его
		sleep(1);
	}
	return 0;
}
