#include"lib.c"

char *fc[]={"100","101","102","103"};

void writereq(char * r , char *port , char * fc)
{
	char *file= myjoin( myjoin(port,"file") , fc ); 
	
	int fd=open( file , O_CREAT | O_WRONLY | O_TRUNC ,0644);
	
	if(fd<0)
	{
		perror("file opening failed");
		exit(EXIT_FAILURE);
	}

	write(fd,r,mylen(r));
	
	close(fd);
	
	if(fork()==0)
	{
		char *args[]={"fsend", file , NULL};
		execv(args[0],(char**)args);

	}
}

char* givereq(char* p , char* c ,char* fc)
{
	char *r;
	r=myjoin(p,(myjoin(c,fc)));
	return r;
}

void main(int x , char *args[])
{
	FILE *fp=fopen( args[1] , "r" );
	assert(fp!=NULL);
	
	char size[1];

	fread(size,sizeof(char),1,fp);

	char *port=(char*) malloc (sizeof(char)*(size[0]-48));
	char *capacity=(char*) malloc (sizeof(char)*(size[0]-48));
	char *serverport=(char*) malloc (sizeof(char)*(size[0]-48));

	fread((void*)port,sizeof(char),4,fp);
	fread((void*)capacity,sizeof(char),4,fp);
	fread((void*)serverport,sizeof(char),4,fp);

	//printf("%s %s %s",port , capacity,serverport);

	char *r;
	
	if(myatoi(port)==myatoi(serverport))
	{
		printf("Cannot be same as server port(%s)",serverport);
		printf("Enter correct port no");
		int pt;
		scanf("%s",port);
	}
	if(mylen(port)<4)
	{	printf("incorrect port number:%s",port);
		printf("Enter correct port number :");
		scanf("%s",port);	
	}
	
	if(mylen(capacity)<4)
	{
		printf("Incorrect capacity :%sEnter correct capacity(in 4 digit format)",capacity);
		scanf("%s",capacity);
	}
	
	int c=1;
	while(c!=0)
	{
		int ch;
		printf("Enter choice (1-4)");
		scanf("%d",&ch);
		if(ch>0 && ch <5)
		{
			r=givereq(port,capacity,fc[ch-1]);
			writereq(r,port,fc[ch-1]);
		}
		else
		{
			free(port);
			free(capacity);
			free(serverport);
			fclose(fp);
			c=0;
		}
	}
}
