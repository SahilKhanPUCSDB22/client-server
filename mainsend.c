#include"lib.c"
#include<stdio.h>
#include<stdlib.h>
#include<arpa/inet.h>
#include<netinet/in.h>
#include<unistd.h>
#include<fcntl.h>
#include<string.h>
#include<assert.h>

#define serverport 1234
char * files[]={"file1","file2","file3","file4"};

void main(int x , char *args[])
{
	assert(mylen(args[1])==4);
	write(1,"sending to :",12);
	write(1,args[1],mylen(args[1]));
	int port=myatoi(args[1]);
	int capacity=myatoi(args[2]);
	int fc=myatoi(args[3]);

	int sockfd;
	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("sockey syscall failed");
		exit(EXIT_FAILURE);
	}
	
	struct sockaddr_in receiveraddr;

	memset(&receiveraddr,0,sizeof(receiveraddr));

	receiveraddr.sin_family=AF_INET;
	receiveraddr.sin_port=htons(port);
	receiveraddr.sin_addr.s_addr=INADDR_ANY;

	char c[]={"11"};
	sendto(sockfd,(void*)c,mylen(c),0,(const struct sockaddr*)&receiveraddr,sizeof(receiveraddr));

	usleep(capacity);

	char * buffer=malloc(sizeof(char)*capacity);

	int fd=open(files[fc-100], O_RDONLY);
	int size=lseek(fd,0,SEEK_END);
	lseek(fd,0,SEEK_SET);
	
	while(size!=0)
	{
		int n = read(fd,buffer,capacity);
		sendto(sockfd,(void*)buffer,n,0,(const struct sockaddr*)&receiveraddr,sizeof(receiveraddr));
		size=size-n;
	}
	write(1,"done",4);

}

