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
        int ps,pc;
        printf("Agent Server Port -");
        scanf("%d",&ps);
        printf("Agent Client Port -");
        scanf("%d",&pc);
       

                int s1 = socket(AF_INET , SOCK_STREAM , 0);
                serv.sin_family = AF_INET;
                serv.sin_port = htons(ps);
                serv.sin_addr.s_addr = htonl(INADDR_ANY);
                int k = bind(s1 , (struct sockaddr *)&serv , sizeof(serv));
                listen(s1,5);
                int size1 = sizeof(client);
                int ns = accept(s1 , (struct sockaddr *)&client , &size1);
                
                struct add abc;
                int f = recv(ns ,&(abc) , sizeof(abc) , 0);
                printf("Received -%s.\n",abc.name);
                printf("Received -%s.\n",abc.data);


                int s2 = socket(AF_INET, SOCK_STREAM, 0);
                serv.sin_family = AF_INET;
                serv.sin_port = htons(pc);
                serv.sin_addr.s_addr = inet_addr("127.0.0.1");
                int size2 = sizeof(serv);
                connect(s2 , (struct sockaddr *)&serv , sizeof(serv));
                printf("Connected to server\n");

                send(s2 , &(abc) , sizeof(abc) , 0); 
                
                recv(s2 ,opt1 , sizeof(opt1) , 0);
                
                send(ns ,opt1 , sizeof(opt1) , 0);

        close(ns);
        close(s1);
        close(s2);
}

