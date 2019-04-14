#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<stdlib.h>
#include<stdio.h>

#define n_stud 4
struct stud{
	char reg[500];
	char name[500];
	char add[500];
	char sub[4][500];
	char dep[500];
	char courses[500];
};

struct stud db[n_stud] = {
	{"160953572", "Samyuktha", "Mumbai", {"100", "99", "98", "97"}, "ICT", "Big data, TCP/IP, Algo"},
	{"160953576", "Shourya", "Farizabad", {"10", "9", "8", "7"}, "ICT", "Big data, Algo"},
	{"160953262", "Shravya","India", {"50", "50", "50", "50"}, "ICT", "TCP/IP, Algo"},
	{"160953031", "Avinish", "", {"69", "42.0", "48.9", "91.1"}, "Mech", "Crafts, Welding"}
};

void find_by_reg(char buff[]){
	int i;
	for(i=0; i<n_stud; i++){
		if(!strcmp(buff, db[i].reg)){
			break;
		}
	}
	if(i==n_stud){
        sprintf(buff, "%s", "Not found");
	} else {
		sprintf(buff, "Name: %s\nAdd: %s", db[i].name, db[i].add);
	}
}

void find_by_name(char buff[]){
	int i;
	for(i=0; i<n_stud; i++){
		if(!strcmp(buff, db[i].name)){
			break;
		}
	}
	if(i==n_stud){
        sprintf(buff, "%s", "Not found");
	} else {
		sprintf(buff, "Dept: %s\nCourses: %s", db[i].dep, db[i].courses);
	}
}

void find_by_code(char buff[]){
	int code;
	code = atoi(buff);
	int i;
	strcpy(buff, "");
	if(code<4){
		for(i=0; i<n_stud; i++){
			sprintf(buff, "%sName: %s\tScore: %s\n", buff, db[i].name, db[i].sub[code]);
		}
	} else {
		strcpy(buff, "Subject not found");
	}
}

    main() {
        int s, r, recb, sntb, x, ns, a = 0;
        printf("INPUT port number: ");
        scanf("%d", & x);
        socklen_t len;
        struct sockaddr_in server, client;
        char buff[500];

        s = socket(AF_INET, SOCK_STREAM, 0);
        if (s == -1) {
            printf("\nSocket creation error.");
            exit(0);
        }
        printf("\nSocket created.");

        server.sin_family = AF_INET;
        server.sin_port = htons(x);
        server.sin_addr.s_addr = htonl(INADDR_ANY);

        r = bind(s, (struct sockaddr * ) & server, sizeof(server));
        if (r == -1) {
            printf("\nBinding error.");
            exit(0);
        }
        printf("\nSocket binded.");

        r = listen(s, 1);
        if (r == -1) {
            close(s);
            exit(0);
        }
        printf("\nSocket listening.");

        len = sizeof(client);

        ns = accept(s, (struct sockaddr * ) & client, & len);
        if (ns == -1) {
            close(s);
            exit(0);
        }
        printf("\nSocket accepting.");

        recb = recv(ns, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            close(ns);
            exit(0);
        }
        
        int opt = atoi(buff);
        
        recb = recv(ns, buff, sizeof(buff), 0);
        if (recb == -1) {
            printf("\nMessage Recieving Failed");
            close(s);
            close(ns);
            exit(0);
        }
        int pid = fork();
        if(!pid){
        	switch(opt){
				case 1:
					printf("Reg no: %s", buff);
					find_by_reg(buff);
					break;
				case 2:
					printf("Name: %s", buff);
					find_by_name(buff);
					break;
				case 3:
					printf("Sub code: %s", buff);
					find_by_code(buff);
					break;
			}
        } else {
        	sprintf(buff, "PID: %d", pid);
        }
		    
        sntb = send(ns, buff, sizeof(buff), 0);
        if (sntb == -1) {
            printf("\nMessage Sending Failed");
            close(s);
            close(ns);
            exit(0);
        }

        close(ns);
        close(s);
        printf("Exit\n");
        exit(0);
    }
