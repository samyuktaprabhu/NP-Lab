#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
struct Bank
{	
	char username[50];
	char password[50];//stored in encrypted format
	float balance;
};
char * decode(char *str)
{

}
void main()
{
	struct Bank b1[3];
	strcpy(b1[0].username,"tom");
	strcpy(b1[1].username,"avi");
	strcpy(b1[2].username,"sam");
	strcpy(b1[0].password,"pwwq");//mttn
	strcpy(b1[1].password,"pdqdv");//manas
	strcpy(b1[2].password,"srvw");//post
	b1[0].balance=1000;
	b1[1].balance=5000;
	b1[2].balance=19000;
	int s,r,recb,sntb,x,ns,a=0,i;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50],usr[50],pass[50],ch[1];
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
	r=listen(s,1);

	if(r==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket listening.");
	len=sizeof(client);
	ns=accept(s,(struct sockaddr*)&client, &len);//client
	if(ns==-1)
	{
		close(s);
		exit(0);
	}

	printf("\nSocket accepting\n");

	printf("\nReading username");
	recb=recv(ns,buff,sizeof(buff),0);//receive from client  // reccciiieeeevvveeee 1
	printf("username recieved");
	strcpy(usr,buff);
	printf("\nReading password");	
	recb=recv(ns,buff,sizeof(buff),0); // recieve from client // reccciiieeeevvveeee 2
	printf("Password recieved");
	strcpy(pass,buff);
	int ii=0;
	for(i=0;i<3;i++)
	{
		if((strcmp(b1[i].username,usr)==0)&&(strcmp(b1[i].password,pass)==0))//found
		{
			x=1;
			ii=i;
			break;			
		}
	}
	printf("\nCustomer found\n");
	
	if(x==1)
	{
		printf("Valid \n Balance = %f",b1[ii].balance);
		//strcpy(buff,ch);
		//sntb=send(s,buff,sizeof(buff),0);
	}
	else
	{
		printf("Invalid\n");
		if(strcmp(b1[i].username,usr)!=0)// not found
		{
			printf("Invalid username");		
		}
		else
		printf("Invalid password");
		
		exit(0);
		//strcpy(buff,"4");
		//sntb=send(s,buff,sizeof(buff),0);
	}
	recb=recv(ns,buff,sizeof(buff),0); // reccciiieeeevvveeee 3
	strcpy(ch,buff);
	printf("\nstring ch copied %s \n",ch);
while(1){
	printf("\n----------------------------------------------------------\n");
	printf("\n ch is %s \n",ch);
	recb=recv(ns,buff,sizeof(buff),0); // reccciiieeeevvveeee 4
	printf("\n MONEYYYYY : %s",buff);
	printf("\n");

	if(ch[0]=='1')
	{
		printf("\n ch is %s xxxxxxxxxxx \n",ch);
		printf("\nRecieved the amount : %s",buff);
		b1[ii].balance-=atof(buff);
		printf("Baaalance : %f",b1[ii].balance);
printf("\n----------------------------------------------------------\n");
	}
	else if(ch[0]=='2')
	{
		printf("\nRecieved the amount : %s",buff);
		b1[ii].balance+=atof(buff);
		printf("Baaaalance : %f",b1[ii].balance);
printf("\n----------------------------------------------------------\n");
	}	
	else if(ch[0]=='3')
	{
		printf("Baaalance : %f",b1[ii].balance);
printf("\n----------------------------------------------------------\n");
	}
//	else {printf("Anythingggggggggggggggggggg");	}
}
//}	//sntb=send(ns,buff,sizeof(buff),0);
close(ns);
	close(s);	
}
