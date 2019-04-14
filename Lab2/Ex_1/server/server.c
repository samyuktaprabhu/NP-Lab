#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

int main()
{
	char *data;
	char ca;
	char msg[1024];
	int i , j , k , p;
	char opt[1024] = "1. Search \n2. Replace \n3. Reorder \n4. Exit \n ";
	char buf[1024];

	int s,r,recb,sntb,x;
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];

	s=socket(AF_INET,SOCK_DGRAM,0);
	if(s==-1)
	{printf("\nSocket creation error.");exit(0);}
	printf("\nSocket created.");

	server.sin_family=AF_INET;server.sin_port=htons(x);server.sin_addr.s_addr=htonl(INADDR_ANY);len=sizeof(client);
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	if(r==-1)
	{printf("\nBinding error.");exit(0);}
	printf("\nSocket binded.");


	recb=recvfrom(s,buff,sizeof(buff),0,(struct sockaddr*)&client,&len);
	if(recb==-1)
	{printf("\nMessage Recieving Failed");close(s);exit(0);}	
	printf("\nMessage Recieved: %s\n",buff);

	int d = sendto(s , opt , sizeof(opt) , 0, (struct sockaddr*)&client,len);
	
	char op[3];
	int f = recvfrom(s ,op , sizeof(op) , 0, (struct sockaddr*)&client,&len);
	int o;
	sscanf(op , "%d" , &o);
	printf("Option Received = ");
	printf("%d\n", o);
	if(o == 4)
	{
	exit(0);
	}
	int sd = recvfrom(s , buf , sizeof(buf) , 0, (struct sockaddr*)&client,&len);
	printf("File name Received is : %s \n" , buf);
	FILE * fp;
	long lSize;
	fp = fopen ( buf , "rb" );
	if( !fp )
	{
	strcpy(msg , "File Not Present !");
	sendto(s , msg , sizeof(msg) , 0, (struct sockaddr*)&client,len);
	exit(1);
	}
	else
	{
	fseek( fp , 0L , SEEK_END);
	lSize = ftell( fp );
	rewind( fp );
	data = calloc( 1, lSize+1 );
	if( !data )
	{
	fclose(fp);
	fputs("memory alloc fails",stderr);
	exit(1);
	}
	if( 1!=fread( data , lSize, 1 , fp) )
	{
	fclose(fp);
	free(data);
	fputs("entire read fails",stderr);
	exit(1);
	}
	fclose(fp);
	printf("\n\n");
	printf("%s\n", data);
	printf("\n");
	sendto(s , data , 1024 , 0,(struct sockaddr*)&client,len);
	}
	if(o == 1)
	{
	char src[1024];
	recvfrom(s , src ,sizeof(src) , 0,(struct sockaddr*)&client,&len);
	printf("Word to be Searched is : %s\n", src);
	int l1 = strlen(data);
	int l2 = strlen(src);
	int count = 0 ; int count1 = 0;
	for(i=0 ; i<l1 ;)
	{
	j=0;
	count = 0;
	while((data[i] == src[j]))
	{
	count++;
	i++;
	j++;
	}
	if(count == l2)
	{
	count1++;
	count = 0;
	}
	else i++;
	}
	if(count1 == 0)
	{
	strcpy(msg , "String Not Found !");
	printf("%s\n", msg);
	}
	else
	{
	strcpy(msg , "Count is : ");
	char dem[3];
	sprintf(dem , "%d" , count1);
	strcat(msg , dem);
	printf("%s\n", msg);
	}
	sendto(s , msg , sizeof(msg) , 0,(struct sockaddr*)&client,len );
	}
	if(o == 2)
	{
	char str1[1024];
	char str2[1024];
	recvfrom(s , str1 , sizeof(str1) ,0,(struct sockaddr*)&client,&len);
	recvfrom(s , str2 , sizeof(str2) , 0,(struct sockaddr*)&client,&len);
	printf("String to be replaced is : %s\n", str1);
	printf("String that replaces is : %s\n", str2);
	char *pf;
	static char buffer[1024];
	if(!(pf = strstr(data , str1)))
	{
	printf("String to be replaced is not found \n");
	strcpy(msg , "String to be replaced is not found \n");
	sendto(s , msg , sizeof(msg) ,0,(struct sockaddr*)&client,len);
	}
	else
	{
	strncpy(buffer , data , pf-data);
	buffer[pf-data] = '\0';
	sprintf(buffer + (pf-data) , "%s%s" , str2 , pf+strlen(str1));
	printf("\nReplaced Data is : \n\n %s \n\n", buffer);
	sendto(s , buffer , 1024 ,0,(struct sockaddr*)&client,len);
	}
	}
	if(o == 3)
	{
	char temp;
	int li, lj;
	for(li=0;data[li];li++)
	{
	for(lj=li+1;data[lj];lj++)
	{
	if(data[lj]<data[li])
	{
	temp=data[lj];
	data[lj]=data[li];
	data[li]=temp;
	}
	}
	}
	printf("The ASCII SORTED STRING IS --------> \n\n%s\n\n",data);
	sendto(s , data , 1024 , 0,(struct sockaddr*)&client,len);
	}


	close(s);
}
