#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <arpa/inet.h>

#define BLOCK_SIZE 1024

int main(void)
{
int serverfd = 0,n = 0;
struct sockaddr_in serv_addr;
char buffer[BLOCK_SIZE];
int revCnt = 0;
memset(buffer, '0' ,sizeof(buffer));
if((serverfd = socket(AF_INET, SOCK_STREAM, 0))< 0)
{
printf("\n Error : Could not create socket \n");
return 1;
}
serv_addr.sin_family = AF_INET;
serv_addr.sin_port = htons(5000);
serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
if(connect(serverfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr))<0)
{
printf("\n Error : Connect Failed \n");
return 1;
}
do
{
  fgets(buffer, sizeof(buffer), stdin);
  write(serverfd, buffer, sizeof(buffer));
  //memset(buffer,'0',sizeof(buffer));
  read(serverfd, buffer, sizeof(buffer));
  fputs(buffer, stdout);
  fflush(stdin);
	printf("\n");
}while(strcmp(buffer,"bye\n")!=0);
return 0;
}
