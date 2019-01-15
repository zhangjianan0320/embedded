#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>

int main()
{
	int serv_sock,clnt_sock;
	struct sockaddr_in serv_addr,clnt_addr;
	socklen_t clnt_addr_size;

	serv_sock=socket(AF_INET,SOCK_STREAM,0);
	if(serv_sock<0)
	{
		perror("");
	}
	memset(&serv_addr,0,sizeof(serv_addr));
	serv_addr.sin_family=AF_INET;
	serv_addr.sin_addr.s_addr=htonl(INADDR_ANY);
	serv_addr.sin_port=htons(9991);
	int optval=1;
	setsockopt(serv_sock,SOL_SOCKET,SO_REUSEADDR,&optval,sizeof(optval));

	if(bind(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("bind error\n");
		exit(-1);
	}
	listen(serv_sock,SOMAXCONN);
	clnt_addr_size=sizeof(clnt_addr);
	clnt_sock=accept(serv_sock,(struct sockaddr*)&clnt_addr,&clnt_addr_size);
	if(clnt_sock<0)
	{
		printf("creat error\n");
	}
	char buf[1024];
	printf("connected with ip %s and port %d\n",inet_ntop(AF_INET,&clnt_addr.sin_addr,buf,1024),ntohs(clnt_addr.sin_port));

	while(1)
	{
		memset(buf,0,sizeof(buf));
		ssize_t size=read(clnt_sock,buf,sizeof(buf)-1);
		if(size < 0)
		{
			printf("read error!\n");
		}
		else
		{
			printf("client:%s\n",buf);
		}
	}
	close(clnt_sock);
	close(serv_sock);

	return 0;

}
