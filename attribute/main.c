/*************************************************************************
    > File Name: main.c
    > Author: zjn
    > Mail:zjn 
    > Created Time: 2019年11月19日 星期二 16时13分01秒
 ************************************************************************/

#include<stdio.h>
//construct main之前运行   
//destructor main之后运行
__attribute ((constructor(103))) void init1();
__attribute ((constructor(101))) void init2();
__attribute ((destructor(101))) void init3();

void init1()
{
	printf("hello init1\n");
	return ;
}

void init2()
{
	printf("hello init2\n");
	return ;
}

void init3()
{
	printf("hello init3\n");
}
int main(int argc,char **argv)
{
	printf("hello main\n");

	return 0;
}
