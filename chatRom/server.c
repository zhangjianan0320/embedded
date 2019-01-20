#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <fcntl.h>
#include <pthread.h>


struct Param
{
	int fc;
	char ip[16];
};

void *func(void *p)
{
	struct Param* r=p;
	while(1)
	{
		char msg[1000];
		int n=read(r->fc,msg,sizeof(msg)-1);
		if(msg[0]=='q')
			break;
		if(n <= 0)
			break;
		write(r->fc,msg,n);
		msg[n]='\0';
		printf("%s : %s\n",r->ip,msg);
	}
	close(r->fc);
	printf("%s:quit\n",r->ip);
	free(p);
}


int main(void)
{
	int fd = socket(AF_INET,SOCK_STREAM,0);

	if(fd < 0)
	{
		perror("socket");
		exit(-1);
	}

	struct sockaddr_in si;
	si.sin_family = AF_INET;
	si.sin_addr.s_addr=htons(INADDR_ANY);
	si.sin_port=htons(8890);

	if(bind(fd,(struct sockaddr*)&si,sizeof(si)) < 0)
	{
		perror("bind");
		close(fd);
		exit(0);
	}

	listen(fd,10);
	while(1)
	{
		struct sockaddr_in c;
		socklen_t len=sizeof(c);

		int fc = accept(fd,(struct sockaddr *)&c,&len);
		if(fc<0)
		{
			perror("accept");
		}
		else
		{
			char ip[16];

			inet_ntop(AF_INET,&c.sin_addr,ip,sizeof(ip));
			printf("%s online\n",ip);
			char msg[1000];
			sprintf(msg,"Your IP:%s,welcom to server\n",ip);
			write(fc,msg,strlen(msg));
//			close(fc);
			pthread_t pid;
			struct Param* p=malloc(sizeof(struct Param));
			p->fc = fc;
			strcpy(p->ip,ip);
			pthread_create(&pid,NULL,func,p);
		}
	}

	return 0;



}
