#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>

int main()
{

        struct sockaddr_in serv;
        struct sockaddr_in client;
        char opt1[1024]="",opt2[1024]="";
        int s = socket(AF_INET , SOCK_STREAM , 0);
        int p;
        printf("Port -");
        scanf("%d",&p);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = inet_addr("127.0.0.1");
        int size = sizeof(serv);
        int xyz = connect(s , (struct sockaddr *)&serv , sizeof(serv));
        printf("%d Connected\n",xyz);

        printf("Enter filename that you wish to send:\n");
        char name[30];
        scanf("%s",name);
        send(s , name , sizeof(name) , 0);

        recv(s ,opt1 , sizeof(opt1) , 0); // wait till done
        printf("%s",opt1);

        FILE *fp;
        char f[99999];
        fp = fopen(name,"rb");
        fread(f,99999,1,fp);
        printf("%s",f);
        //d = send(s , f , sizeof(f) , 0);
        fclose(fp);

        
        
        close(s);
}

