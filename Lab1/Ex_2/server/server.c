#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
main()
{
int s,r,recb,sntb,x;
int ca;
printf("INPUT port number: ");
scanf("%d", &x);
socklen_t len;
struct sockaddr_in server,client;
char buff[50];
s=socket(AF_INET,SOCK_DGRAM,0);
if(s==-1)
{
printf("\nSocket creation error.");
exit(0);
}
printf("\nSocket created.");
server.sin_family=AF_INET;
server.sin_port=htons(x);
server.sin_addr.s_addr=htonl(INADDR_ANY);
len=sizeof(client);
ca=sizeof(client);
r=bind(s,(struct sockaddr*)&server,sizeof(server));
if(r==-1)
{
printf("\nBinding error.");
exit(0);
}
printf("\nSocket binded.");

/////////////////////////
while(1){
recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&ca);
if(recb==-1)
{
printf("\nMessage Recieving Failed");
close(s);
exit(0);
}

printf("\nMessage Recieved: ");
printf("%s", buff);

int i,j,l=0,flag=1;
for(i=0;buff[i]!='\0';i++)
{
l=l+1;
}
printf("\n Length of the String is : %d \n ",l);


for(i=0;i<l;i++)
{
 if(buff[i]!=buff[l-i-1])
 {
 flag=0;
 break;
 }
}
if(flag==1)
{
printf("\n Yes, It is a Palindrome! \n ");
printf("\n\n");
}
else
{
printf("\n No, It is not a Palindrome!\n ");
printf("\n\n");
}

int ac=0,ec=0,ic=0,oc=0,uc=0,rc=0;

for(i=0;i<l;i++)
{
if(buff[i]=='a' || buff[i]=='A')
{
ac+=1;
}
else if(buff[i]=='e' || buff[i]=='E')
{
ec+=1;
}
else if(buff[i]=='i' || buff[i]=='I')
{
ic+=1;
}
else if(buff[i]=='o' || buff[i]=='O')
{
oc+=1;
}
else if(buff[i]=='u' || buff[i]=='U')
{
uc+=1;
}
else
{
rc+=1;
}

}
printf("\n A count : %d",ac);
printf("\n E count : %d",ec);
printf("\n I count : %d",ic);
printf("\n O count : %d",oc);
printf("\n U count : %d",uc);

if(!strcmp(buff,"halt"))
break;
printf("\n\n");
printf("Type Message: ");
scanf("%s", buff);
sntb=sendto(s,buff,sizeof(buff),0,(struct sockaddr*)&client,len);
if(sntb==-1)
{
printf("\nMessage Sending Failed");
close(s);
exit(0);
}
if(!strcmp(buff,"halt"))
break;
}
close(s);
}

