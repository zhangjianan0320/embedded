#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>

int main(int argc,char *argv[])
{
	if(argc!=3)
	{
		printf("input error\n");
		exit(-1);
	}
	int fd=socket(AF_INET,SOCK_STREAM,0);
	struct sockaddr_in c;
	c.sin_family=AF_INET;
	inet_pton(AF_INET,argv[1],&c.sin_addr);
	c.sin_port=htons(atoi(argv[2]));
	if(connect(fd,(struct sockaddr *)&c,sizeof(c)) < 0)
	{
		perror("connect");exit(-1);
	}
	char msg[1000];
	while(1)
	{
		int num=read(fd,msg,sizeof(msg)-1);
		//int num=recv(fd,msg,sizeof(msg),0);
		
		if(num<=0)
			break;
		msg[num]='\0';
		write(STDOUT_FILENO,msg,num);
		scanf("%s",msg);
		strcat(msg,"\n");

		write(fd,msg,strlen(msg));
		//send(fd,msg,strlen(msg),0);

		if(msg[0]=='q')
			break;
	}
	close(fd);
	return 0;
}
