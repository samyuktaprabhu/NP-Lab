#include<string.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<fcntl.h>
#include<sys/stat.h>

int  main()
{
	char buf[1024] , str[1024];

	struct sockaddr_in  serv ;
	socklen_t size;

	printf("Enter Port Number : ");
	int p ;
	scanf("%d" , &p);
	printf("\n");

	int s;
	s = socket(AF_INET , SOCK_STREAM , 0);
	if( s == -1)
	{
		printf("%s\n", "Socket not created");
		exit(0);
	}
	printf("Socket created\n");


	serv.sin_family = AF_INET;
	serv.sin_port = htons(p);
	serv.sin_addr.s_addr = inet_addr("127.0.0.1");

	int r;

	r = connect (s , (struct sockaddr * )&serv , sizeof(serv));

	if( r == -1 )
	{
		printf("Connection failed \n");
		close(s);
		exit(0);
	}
	else
	{
		printf("Connection successful\n");
	}

	printf("Enter an alphanumeric string: ");
	wapis: scanf("%s" , buf);
	int sd;
	sd = send(s , buf , sizeof(buf) , 0);

	if( sd < 0)
	{
		printf("String can't be sent\n");
		printf("Enter string again\n");
		goto wapis;
	}
	else
	{
		printf("Check the server side for output\n");
	}
	close(s);
}
