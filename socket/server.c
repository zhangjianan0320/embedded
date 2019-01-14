#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define MYPORT 8888
#define BACKLOG 10

int main(void)
{
	int sockfd;
	struct sockaddr_in my_addr;

	memset(&my_addr,0,sizeof(my_addr));
	my_addr.sin_family=AF_INET;
	my_addr.sin_port=htons(MYPORT);
	my_addr.sin_addr.s_addr=INADDR_ANY;

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	bind(sockfd,(struct sockaddr *)&my_addr,sizeof(struct sockaddr));

	listen(sockfd,BACKLOG);

	int new_fd;
	struct sockaddr_in their_addr;
	int sin_size;
	sin_size=sizeof(struct sockaddr_in);
	new_fd=accept(sockfd,(struct sockaddr *)&their_addr,&sin_size);

	if(!fork())
	{
		if(send(new_fd,"hellow world!\n",14,0) == -1)
		{
			perror("send");
		}
		close(new_fd);
		exit(1);
	}
	close(new_fd);


}
