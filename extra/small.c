

#define large 1234
#define caplimit 4
int capacity;
char** filecode[]={"00","01","10","11"};

char* assemble( char* f, char * cap , char* choice )
{
	int fd=open(f, O_WRONLY | O_APPEND , 0644 );
	write(fd,cap,sizeof(cap));
	write(fd,choice,sizeof(choice));
	return fd;
}
		
void getfile(char *f , char *capacity , int choice)
{
	int *fd=assemble(f,capacity,filecode[choice]);
	char buffer[14];

	
}

int main(int x,char* f[])
{
	int port,capp;
	scanf("%d",&port); //port no of this system
	scanf("%d",&capp); //capacity of this system
	capacity=capp;  //used in multiple functions

	char* cap=malloc(sizeof(char)*caplimit);
	sprintf(cap,"%d",capacity);
	
	int c=1,choice;
	while(c!=0)
	{
		printf("Enter required file\n1.file1\n2.file2\n3.file3\n4.file4\n5.exit\n");
		scanf("%d",&choice);
		if (choice>0 && choice<5)
		{
			getfile(f[1],cap,choice);
		}
		else if(choice==5)
		{
			c=0;
		}
		else
		{
			printf("Wrong choice");
		}
	}
	return 0;
}
		 

