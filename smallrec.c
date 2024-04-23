#include"lib.c"

void main(int x , char* file[])
{	
	//write(1,"\nrecs",5);
	int sockfd,len;

	int fd=open(file[1],O_RDONLY);
	if(fd<0)
	{
		perror("file failure");
		exit(0);
	}

	char p[5],c[5];

	read(fd,p,4);
	read(fd,c,4);
	
	p[4]='\0';
	c[4]='\0';

	close(fd);

	int port,capacity;

	port=myatoi(p); capacity=myatoi(c);	

	struct sockaddr_in receiverAddr, senderAddr;
	
	if((sockfd=socket(AF_INET, SOCK_DGRAM,0))<0)
 	{
    	perror("socket system call failed");
    	exit(EXIT_FAILURE);
  	}
	
  	memset(&receiverAddr, 0, sizeof(receiverAddr));
  	memset(&senderAddr, 0, sizeof(senderAddr));
	
	len=sizeof(senderAddr);

  	receiverAddr.sin_family = AF_INET;
  	receiverAddr.sin_addr.s_addr = INADDR_ANY;
  	receiverAddr.sin_port = htons(port);

	if(bind(sockfd, (const struct sockaddr *)&receiverAddr, sizeof(receiverAddr)) < 0)
  	{
    	perror("bindd syscall failed");
    	exit(EXIT_FAILURE);
  	}

	int rb=0;
        char *buffer=malloc(sizeof(char)*3);	
	
	rb = recvfrom(sockfd,(void*)buffer, 2 , MSG_WAITALL, (struct sockaddr *) &senderAddr, &len );
	buffer[rb]='\0';
	
	if(atoi(buffer)==11)
	{
		free(buffer);
		buffer=malloc(sizeof(char)*capacity);

		int l=0;

		fd=open(file[1],O_WRONLY | O_CREAT | O_TRUNC,0644);
		if (fd<0) 
		{
			perror("opening f");
			exit(0);
		}

		while(l!=1)
		{
			rb=recvfrom(sockfd,(void*)buffer , capacity , MSG_WAITALL , (struct sockaddr*) & senderAddr , &len);
			if(rb < capacity)
			{
				write(fd,buffer,rb);
				l=1;
			}

			else
			{
				write(fd, buffer , rb);
			}
		}
		close(fd);
	}
	system("echo 'File Recieved'");
	//write(1,"\nrece",5);
}



