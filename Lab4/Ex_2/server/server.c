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
}abc;
int main()
{
        struct sockaddr_in serv;
        struct sockaddr_in client;
        char opt1[1024]="",opt2[1024]="";
        int p;
        printf("Server Port -");
        scanf("%d",&p);
        int s = socket(AF_INET , SOCK_STREAM , 0);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);
        int k = bind(s , (struct sockaddr *)&serv , sizeof(serv));
        listen(s,5);
        int size = sizeof(client);
        int ns = accept(s , (struct sockaddr *)&client , &size);

                        int f = recv(ns ,&abc , sizeof(abc) , 0);
                        printf("Received -%s.\n",abc.data);

                        char msg[30] = "hello from server";
                        int d = send(ns , msg , sizeof(msg) , 0);
                        printf("Sent/n");
                        /*
                        
                        if(strcmp(opt2,"bye")==0){close(ns);close(s);kill(pid,9);exit(0);}   */

        close(ns);
        close(s);
}

