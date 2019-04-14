#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
main()
{
int s,r,recb,sntb,x,ns,a=0;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
s=socket(AF_INET,SOCK_STREAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("\nSocket binded.");
r=listen(s,3);
if(r==-1)
{
close(s);
exit(0);
}
printf("\nSocket listening.");
len=sizeof(client);
ns=accept(s,(struct sockaddr*)&client, &len);
if(ns==-1)
{
close(s);
exit(0);
}
////////////////////////////////////////////////
int arr[100];
printf("\nSocket accepting.");
recb=recv(ns,&arr,sizeof(arr),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed : Array");
close(s);
close(ns);
exit(0);
}
int choice;
recb=recv(ns,&choice,sizeof(choice),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed : Choice");
close(s);
close(ns);
exit(0);
}
int N;
recb=recv(ns,&N,sizeof(N),0);
if(recb==-1)
{
printf("\nMessage Recieving Failed : N");
close(s);
close(ns);
exit(0);
}
int n;
int jj=0,kk=0;
//recb=recv(ns,&n,sizeof(n),0);
/**if(recb==-1)
{
printf("\nMessage Recieving Failed : N");
close(s);
close(ns);
exit(0);
}**/
int j,k,l,flag1=0,odd[100],even[100];
switch(choice){

case 1: 
       printf("Enter the number to be searched");
       int n;
       scanf("%d",&n);
     //  recb=recv(ns,&n,sizeof(n),0);
       // if(recb==-1)
      /** {
        printf("\nMessage Recieving Failed : N");
        close(s);
        close(ns);
        exit(0);
    }**/
       
       for(j=0;j<N;j++)
	{
		if(arr[j]==n)
		{
			printf("\n Found");
			flag1=1;
		}
	}
	if(flag1==0)
	printf("\n Not found");
	break;
case 2: for(j=0;j<N;j++)
	{
		for(k=j+1;k<N;k++)
		{
			if(arr[j]>arr[k])
			{
			 int temp;
			 temp=arr[j];
			 arr[j]=arr[k];
			 arr[k]=temp;
			}

	}
	}
	printf("\n The ascending order is");
	for(j=0;j<N;j++)
	{
	 printf("%d",arr[j]);
	}
	break;
case 3: for(j=0;j<N;j++)
	{
		for(k=j+1;k<N;k++)
		{
			if(arr[j]>arr[k])
			{
			 int temp;
			 temp=arr[j];
			 arr[j]=arr[k];
			 arr[k]=temp;
			}
	}
	}
	printf("\n The descending order is");
	for(j=0;j<N;j++)
	{
	 printf("%d",arr[j]);
	}
	break;
case 4:
	for(j=0;j<N;j++)
	{
		if(arr[j]%2==0)
		{
		 even[jj++]=arr[j];
		}
		else
		{
		 odd[kk++]=arr[j];
		}
	}
	printf("\n The even numbers are : ");
	for(j=0;j<jj;j++)
	{
	 printf("%d",even[j]);
	}
	printf("\n The odd numbers are : ");
	for(j=0;j<kk;j++)
	{
	 printf("%d",odd[j]);
	}
	break;
default: printf(" some error");
	

}

/////////////////////////////////////////////////////////////////////////////////////
//printf("\nMessage Recieved: ");
//printf("%s", buff);
//printf("\n\n");
//scanf("%s", buff);
//sntb=send(ns,buff,sizeof(buff),0);
//if(sntb==-1)
//{
//printf("\nMessage Sending Failed");
//close(s);
//close(ns);
//exit(0);
//}
close(ns);
close(s);
}
