/*************************************************************************
    > File Name: main.c
    > Author: zjn
    > Mail:zjn 
    > Created Time: 2019年10月22日 星期二 17时54分39秒
 ************************************************************************/

#include<stdio.h>

void main(int argc,char **argv)
{
	int ack = 1;
	int i = 3;
	while(i-- && ack != 0)
	{
		ack = 0;
		printf("while times is %d\n",i);
	}

	int num=256;
	printf("%d.%d\n",num/256,num%256);
	num=255;
	printf("%d.%d\n",num/256,num%256);
	num=0x0203;
	printf("%d.%d\n",num/256,num%256);


/*
	FT_Error	error;
	FT_Library lib;
	FT_Face	face;

	char *filename;
	char *text;

	if(argc!=3)
	{
		printf("input error:\n");
	}

	filename=argv[1];
	text=argv[2];

	error=FT_Init_FreeType(&lib);
	error=FT_New_Face(lib,filename,0,&face);

	if(error)
	{
		printf("error %d\n",error);
		exit(0);
	}
*/
	return ;

}
