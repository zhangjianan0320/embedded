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
	serv_addr.sin_addr.s_addr=inet_addr("127.0.0.1");
	serv_addr.sin_port=htons(9991);


	if(connect(serv_sock,(struct sockaddr*)&serv_addr,sizeof(serv_addr)) < 0)
	{
		printf("con\n");
	}

	if(clnt_sock<0)
	{
		perror("");
	}

	while(1)
	{
		ssize_t size=write(serv_sock,"123",3);
	}
	close(clnt_sock);

	return 0;

}
