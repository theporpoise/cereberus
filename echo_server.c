#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>

int main(void)
 {
	int clientfd = 0;
	int connfd = 0;
	int n = 0;
	struct sockaddr_in serv_addr;
	char buffer[1024];

	clientfd = socket(AF_INET, SOCK_STREAM, 0);
	printf("socket retrieve success\n");
	memset(&serv_addr, '0', sizeof(serv_addr));
	memset(buffer, '0', sizeof(buffer));
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	serv_addr.sin_port = htons(5000);
	bind(clientfd, (struct sockaddr*)&serv_addr,sizeof(serv_addr));
	if(listen(clientfd, 10) == -1)
	{
		printf("Failed to listen\n");
		return -1;
	}
	connfd = accept(clientfd, (struct sockaddr*)NULL ,NULL);
	while(1)
	{
		read(connfd, buffer, sizeof(buffer));
		write(connfd, buffer, sizeof(buffer));
		fputs(buffer,stdout);
	}
	close(connfd);
	return 0;
	}
