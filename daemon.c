#include <unistd.h>
#include <signal.h>
#include <sys/param.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
void init_daemon(void)
{
	int pid;
	int i;
	//退出父进程
	if(pid = fork())
		exit(0);
	else
		if(pid < 0)//fork失败退出
			exit(1);
	//第一子进程后台执行
	//将子进程设置为新的会话组长和
	//	进程组长，并与控制终端分离
	setsid();
	//退出第一子进程
	if(pid = fork())
		exit(0);
	else
		if(pid < 0)
			exit(1);

	//此进程在此处关闭所有文件描述符
	for(i = 0;i <	NOFILE;i++)
		close(i);
	//更换工作目录
	chdir(".");
	// 重设文件创建掩膜
	umask(0);

	return;
}

/*int main(int argc, char const *argv[])
{
	init_daemon();
	int fd;
	fd = open(argv[1],O_CREAT|O_RDWR,0777);
	if(fd < 0)
	{
		perror("fd ");
	}
	char buf[10];
	int i;
	for(i = 0;i < 9;i++)
	{
		buf[i] = '2';
	}

	while(1)
	{
		write(fd,buf,1);

	}


	return 0;
}*/