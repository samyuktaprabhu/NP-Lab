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
main()
{
int s,r,recb,sntb,x;
printf("INPUT port number: ");
scanf("%d", &x);
struct sockaddr_in server;
//char buff[50];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=inet_addr("127.0.0.1");
r=connect(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nConnection error.");
exit(0);
}
printf("\nSocket connected.");
printf("\n");
printf("\n);
////////////////////////////////////////////////////////////////////
int arr[100];
int i,N,num;

printf("Enter array size: ");
scanf("%d", &N);

printf("Enter numbers: ");
for(i=0;i<N;i++)
{
scanf("%d",&arr[i]);
}
int choice;
printf("Enter choice : \n 1. Search for a number: \n 2. Sort in ascending order \n 3. Sort in descending order \n 4. Split into odd or even");
scanf("%d",&choice);

sntb=send(s,&arr,sizeof(arr),0);
if(sntb==-1)
{
close(s);
printf("\nMessage Sending Failed : Array");
exit(0);
}
sntb=send(s,&choice,sizeof(choice),0);
if(sntb==-1)
{
close(s);
printf("\nMessage Sending Failed : choice");
exit(0);
}
int xx=N;
sntb=send(s,&xx,sizeof(xx),0);
if(sntb==-1)
{
close(s);
printf("\nMessage Sending Failed : Array");
exit(0);
}
//////////////////////////////////////////////////////////////////////////////
recb=recv(s,&arr,sizeof(arr),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed");
close(s);
exit(0);
}
//printf("\nMessage Recieved! ");
//printf("choice : %d",choice);
//printf("\n\n");
close(s);
}

