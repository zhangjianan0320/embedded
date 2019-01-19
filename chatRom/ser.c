#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <unistd.h>

#define ERR(msg) do{perror(msg);exit(-1);}while(0)
#define PORT 8000
#define IP "192.168.0.11"

int main(void)
{
	int sockfd;
	int val=1;
	int cfd[1024]={0};
	int i=0;
	int maxfd=0;
	int ret=0;
	int rn;
	char msgbuf[1024]={0};

	struct sockaddr_in saddr,caddr;
	saddr.sin_family=AF_INET;
	saddr.sin_port=htons(PORT);
	saddr.sin_addr.s_addr=inet_addr(IP);
	socklen_t slen=sizeof(saddr);
	socklen_t clen=sizeof(caddr);

	fd_set rfds,allfds;

	if((sockfd = socket(AF_INET,SOCK_STREAM,0))<0)
		ERR("socket");
	if(setsockopt(sockfd,SOL_SOCKET,SO_REUSEADDR,&val,sizeof(val))<0)
		ERR("setsockopt");
	if(bind(sockfd,(struct sockaddr *)&saddr,slen)<0)
		ERR("bind");
	if(listen(sockfd,20)<0)
		ERR("listen");
	FD_ZERO(&rfds);
	FD_SET(sockfd,&rfds);
	if(sockfd>maxfd)
		maxfd=sockfd;

	while(1)
	{
		allfds=rfds;
		ret=select(maxfd+1,&allfds,NULL,NULL,NULL);
		if(ret<=0)
		{

			ERR("select");
			continue;
		}
		else
		{
		
			if(FD_ISSET(sockfd,&allfds))
			{
				for(i=0;i<1024;i++)
				{
					if((cfd[i]=accept(sockfd,(struct sockaddr *)&caddr,&clen))<0)
					{
						perror("accept");
						continue;
					}
					printf("clint:ip:%s\tport:%d\n",inet_ntoa(caddr.sin_addr),ntohs(caddr.sin_port));
					FD_SET(cfd[i],&rfds);
					if(cfd[i]>maxfd)
						maxfd=cfd[i];
				}
			}
			for(i=0;i<1024;i++)
			{
				if(FD_ISSET(cfd[i],&allfds))
				{
					rn=recv(cfd[i],msgbuf,sizeof(msgbuf),0);
					if(rn<0)
					{
						ERR("recv");
					}
					else if(rn==0)
					{
						printf("clint close\n");
					}
					else
					{
						printf("msg:%s\n",msgbuf);
					}
				}
			}
		}

	}

	close(sockfd);

}
