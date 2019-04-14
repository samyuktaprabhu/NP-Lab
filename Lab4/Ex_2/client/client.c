#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

struct add
{
        char name[20];
        char data[20];
};
int main()
{
        struct sockaddr_in serv;
        struct sockaddr_in client;
        char opt1[1024]="",opt2[1024]="";
        int s = socket(AF_INET, SOCK_STREAM, 0);
        int p;
        printf("Agent Port -");
        scanf("%d",&p);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");
        int size = sizeof(serv);
        int ns = connect(s , (struct sockaddr *)&serv , sizeof(serv));
        printf("Connected\n");

        struct add abc;
        strcpy(abc.name,"www.socket.com");
        strcpy(abc.data,"hello");
        //scanf("%s",opt2);
        int d = send(s , &abc , sizeof(abc) , 0);
        
        recv(s ,opt1 , sizeof(opt1) , 0);
        printf("Received -%s.\n",opt1);

                
        close(s);
}

