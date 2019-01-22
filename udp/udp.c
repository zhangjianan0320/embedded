#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>

int main(int argc,char *argv[])
{
	if(argc!=2)
	{
		printf("input error!\n");
		return 0;
	}
	int skt=socket(AF_INET,SOCK_DGRAM,0);
	struct sockaddr_in s;
	s.sin_family=AF_INET;
	s.sin_addr.s_addr=INADDR_ANY;
	s.sin_port=htons(atoi(argv[1]));
	if(bind(skt,(struct sockaddr*)&s,sizeof(s)) < 0)
	{
		perror("bind");
		return -1;
	}
	char cmd;
	char ip[16];
	short port;
	char txt[1000];

	while(1)
	{
		printf("s/r/a/q:");
		scanf("%c",&cmd);
		switch(cmd)
		{
			case 'q':
				return 0;
				break;
			case 's':
				{
					scanf("%s%hd %[^\n]",ip,&port,txt);
					s.sin_family=AF_INET;
					inet_pton(AF_INET,ip,&s.sin_addr);
					s.sin_port=htons(port);

					sendto(skt,txt,strlen(txt)+1,0,(struct sockaddr*)&s,sizeof(s));
				}
				break;
			case 'a':
				{
					scanf(" %[^\n]",txt);
					sendto(skt,txt,strlen(txt)+1,0,(struct sockaddr*)&s,sizeof(s));
				}
				break;
			case 'r':
				{
					socklen_t len=sizeof(s);
					int n=recvfrom(skt,txt,sizeof(txt),MSG_DONTWAIT,(struct sockaddr*)&s,&len);
					if(n<=0)
					{
						printf("no data\n");
					}
					else
					{
						inet_ntop(AF_INET,&s.sin_addr,ip,sizeof(ip));
						printf("ip :%s,port %hd,txt:%s\n",ip,ntohs(s.sin_port),txt);
					}
				}
				break;
			default :
				break;


		}

	}
}

