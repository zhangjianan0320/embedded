#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <arpa/inet.h>

int main(int argc,char **argv)
{
	int sockfd;
	struct sockaddr_in their_addr;

	memset(&their_addr,0,sizeof(their_addr));

	sockfd=socket(AF_INET,SOCK_STREAM,0);
	
	their_addr.sin_family=AF_INET;
	their_addr.sin_port=htons(8888);
	their_addr.sin_addr.s_addr=inet_addr("127.0.0.1");

	connect(sockfd,(struct sockaddr*)&their_addr,sizeof(struct sockaddr));

	char *buf="hello !\n";
	send(sockfd,argv[1],strlen(argv[1]),0);

	close(sockfd);



}
