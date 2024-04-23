#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<unistd.h>
#include<fcntl.h>
#include<arpa/inet.h>
#include<netinet/in.h>

#define serverport 1234

void main()
{
	int sockfd;
	int fd=open("requestfile",O_WRONLY | O_TRUNC | O_CREAT , 0644);
	if(fd<0)
	{
		perror("File opening failed");
		exit(EXIT_FAILURE);
	}

	if((sockfd=socket(AF_INET,SOCK_DGRAM,0))<0)
	{
		perror("Socket system call failed");
		exit(0);
	}
	struct sockaddr_in recieveraddr,senderaddr;
	memset(&recieveraddr,0,sizeof(recieveraddr));
	memset(&senderaddr,0,sizeof(senderaddr));
	
	recieveraddr.sin_family=AF_INET;
	recieveraddr.sin_addr.s_addr=INADDR_ANY;
	recieveraddr.sin_port=htons(serverport);

	if(bind(sockfd,(const struct sockaddr*)&recieveraddr,sizeof(recieveraddr))<0)
	{
		perror("Sock bind failed");
		exit(0);
	}

	int len =sizeof(senderaddr);
	char buffer[10];
	while(1)
	{
		int b = recvfrom(sockfd,(char*)buffer,1024,MSG_WAITALL,(struct sockaddr*)&senderaddr,&len);
		//printf("%d",b);
		write(fd,buffer,b);
		//write(1,"r",1);
	}
	close(fd);
	close(sockfd);
}

