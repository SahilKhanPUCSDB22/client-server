#include"lib.c"

#define serverport 1234
void main(int x , char *file[])
{
	//write(1,"reqs",4);
	int sockfd,fd;
	fd=open(file[1],O_RDONLY);
	if(fd<0)
	{
		perror("opening failed");
		exit(0);
	}
	char *r=malloc(sizeof(char)*12);
	read(fd,r,11);
	r[11]='\0';
	struct sockaddr_in receiverAddr;
	if((sockfd=socket(AF_INET, SOCK_DGRAM,0))<0)
	{
		perror("socket failed");
		exit(EXIT_FAILURE);
	}

	memset(&receiverAddr , 0 , sizeof(receiverAddr));
	receiverAddr.sin_family=AF_INET;
  	receiverAddr.sin_port = htons(serverport);
  	receiverAddr.sin_addr.s_addr =INADDR_ANY;
	
	sendto(sockfd,r,11,0,(const struct sockaddr*)&receiverAddr , sizeof(receiverAddr));
	close(sockfd);

	char * args[]={"frec",file[1],NULL};

	execv(args[0],(char**)args);
}
