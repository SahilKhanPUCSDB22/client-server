#include"lib.c"
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>

#define serverport 1234

char* getfc(int fd)
{
	char* fc=malloc(sizeof(char)*4);
        int n=read(fd,fc,3);
	fc[n]='\0';
	return fc;
}
char* getcap(int fd)
{
	char *cap=malloc(sizeof(char)*5);
	int n=read(fd,cap,4);
	cap[n]='\0';
	return cap;
}
char * getport(int fd)
{
	char *port=malloc(sizeof(char)*5);
	int n=read(fd,port,4);
	port[n]='\0';
	return port;
}
void main()
{
	int fd=open("requestfile" , O_CREAT | O_RDWR | O_TRUNC , 0644);
        if(fd<0)
	{
		perror("file o failed");
		exit(EXIT_FAILURE);
	}

	int old = 0;
	
	if(fork()==0)
	{
		char *args[]={"ear",NULL};
		assert((execv("ear",(char**)args))!=-1);
	}

	//usleep(1000);

	int new=0;

	while(1)
	{
		new=lseek(fd , 0 , SEEK_END);
		while(old!=new)
		{
			//write(1,"reqrec",6);
			lseek(fd , old ,SEEK_SET);
			char *p=getport(fd);
			char *c=getcap(fd);
			char *fc=getfc(fd);
	
			if(myatoi(p)==serverport)
			{
				printf("Invalid port number\nEnter correct one\n");
				char xyz[5];
				scanf("%s",xyz);
				p=xyz;
			}
			
			//write(1,"Sending to ",12);
			//write(1,p,4);

			if(fork()==0)
			{
				char *args[]={"msend",p,c,fc,NULL};
				int ex = execv(args[0],(char**)args);
				assert(ex!=(-1));
			}
			old=old+11;
		}
		old=new;
		lseek(fd , 0 , SEEK_SET);
	}
}
