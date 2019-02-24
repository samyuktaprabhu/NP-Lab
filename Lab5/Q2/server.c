#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>
#define MAXSIZE 90
void sort(char *str)
{
    int i;
    for (i = 0; i < strlen(str) - 1; i++)
        for (int j = i+1; j <strlen(str); j++)
            if (str[i] < str[j]) 
            {
                char t = str[j];
                str[j] = str[i];
                str[i] = t;
            }
}
int main()
{
	int s,r,recb,sntb,x,ns,a=0,pid,status;
	char str1[50],str2[50],data[50];
	printf("INPUT port number: ");
	scanf("%d", &x);
	socklen_t len;
	struct sockaddr_in server,client;
	char buff[50];
	s=socket(AF_INET,SOCK_STREAM,0);
	printf("\nSocket created.");
	server.sin_family=AF_INET;
	server.sin_port=htons(x);
	server.sin_addr.s_addr=htonl(INADDR_ANY);
	r=bind(s,(struct sockaddr*)&server,sizeof(server));
	printf("\nSocket binded.");
	r=listen(s,2);
	printf("\nSocket listening.");
///////////////////
	while(1)
	{
		len=sizeof(client);
		ns=accept(s,(struct sockaddr*)&client, &len);
		if(ns==-1)
		{
			close(s);
			exit(0);
		}
		if (recv(ns,buff,sizeof(buff),0) == -1) 
		{
            	printf("\n Error Reading Data from Socket.\n");
            	close(ns);
            	close(s);
            	return -1;
       	    	}        
        	strcpy(str1,buff);

        	if (recv(ns,buff,sizeof(buff), 0) == -1) 
        	{
            	printf("\n Error Reading Data from Socket.\n");
            	close(ns);
            	close(s);
            	return -1;
        	}
        	strcpy(str2,buff);
        	printf(" \nString 1 is : %s \n",str1);
        	printf("\n String 2 is : %s \n",str2);
        	status = 1;
		//printf("\n BEfore comp \n");

        	if(strlen(str1) != strlen(str2))
            	{ //printf("\nInside the len comp \n ");
		status = 0;}
		//printf("\n after comp \n");

        	if(status==1) 
        	{
		printf("\n Sorting \n");
            	sort(str1); 
	    	sort(str2);
            	int i = 0;
            	for (i = 0; i < strlen(str1) && status; i++)
                if (str1[i] != str2[i]) 
		{
		status = 0; 
		break;
		}
		if(status==1)
        	printf("Strings are anagrams");
		else
		printf("Strings are not anagrams");
        	}
        }	
}
