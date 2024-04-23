#include<stdlib.h>
#include<assert.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
#include<stdio.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<sys/types.h>


int myatoi(char*c);
int gnum(char*c , int l);
int cal(char*c , int l);
int mylen(char* c);
char * myjoin(char* a , char* b);


int myatoi(char *c)
{
	long l=mylen(c);
	return gnum(c,l);	
}

int gnum(char *c , int l)
{
	long re;
	if(*(c)=='\0')
	{
		re=0;
	}
	else 
	{
		re=cal(c,(l-1))+gnum(c+1 ,(l-1)) ;
	}
	return re;
}

int cal(char *c , int len)
{
	long re;
	if (len==0)
	{
		re=*(c)-48;
	}
	else 
	{
		re=10 * cal(c,(len-1));
	}
	return re;
}


int mylen(char* c)
{
	int i=0;
	long r=0;
	while(*(c+i)!='\0')
	{
		r=r+1;
		i=i+1;
	}
	return r;
}

char * myjoin(char *a , char* b)
{
	int size=mylen(a)+mylen(b);
	char *temp=malloc(sizeof(char)*(size+1));
	int i=0,j=0;
	int len=mylen(a);
	while(*(b+j)!='\0'  || *(a+i)!='\0')
	{
		if(*(b+j)!='\0')
		{
			temp[len]=*(b+j);
			len=len+1;
			j=j+1;
		}
		if(*(a+i)!='\0')
		{
			temp[i]=*(a+i);
			i=i+1;
		}
	}
	temp[size]='\0';
	return temp;
}


