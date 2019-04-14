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

    main() {
        int s, r, recb, sntb, x;
        printf("INPUT port number: ");
        scanf("%d", & x);
        struct sockaddr_in server;
        char buff[500];
        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1) {
            printf("\nSocket creation error.");
            exit(0);
        }
        printf("\nSocket created.");

        server.sin_family = AF_INET;
        server.sin_port = htons(x);
        server.sin_addr.s_addr = inet_addr("127.0.0.1");

        r = connect(s, (struct sockaddr * ) & server, sizeof(server));
        if (r == -1) {
            printf("\nConnection error.");
            exit(0);
        }
        printf("\nSocket connected.");

        printf("\n\n");
        printf("1. Reg. no.\n2. Name\n3. Sub code\n");
        scanf("%s", buff);
        
        int opt = atoi(buff);
        
        sntb = send(s, buff, sizeof(buff), 0);
        if (sntb == -1) {
            close(s);
            printf("\nMessage Sending Failed");
            exit(0);
        }

		switch(opt){
			case 1:
				printf("Reg no:");
				break;
			case 2:
				printf("Name: ");
				break;
			case 3:
				printf("Sub code [0,1,2,3]: ");
				break;
		}
		
		scanf("%s", buff);
		sntb = send(s, buff, sizeof(buff), 0);
        if (sntb == -1) {
            close(s);
            printf("\nMessage Sending Failed");
            exit(0);
        }
		
        recb = recv(s, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            exit(0);
        }

        printf("\n%s", buff);
        printf("\n\n");
        
        recb = recv(s, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            exit(0);
        }

        printf("\n%s", buff);
        printf("\n\n");

        close(s);
        printf("Exit\n");
        exit(0);
    }
