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
        int p;
        printf("Port -");
        scanf("%d",&p);
        int s = socket(AF_INET , SOCK_STREAM , 0);
        serv.sin_family = AF_INET;
        serv.sin_port = htons(p);
        serv.sin_addr.s_addr = htonl(INADDR_ANY);
        int k = bind(s , (struct sockaddr *)&serv , sizeof(serv));
        listen(s,5);
        int size = sizeof(client);
        int ns = accept(s , (struct sockaddr *)&client , &size);
        


                recv(ns ,opt1 , sizeof(opt1) , 0);
                printf("Filename : %s",opt1);
                FILE *fp;
                char f[99999];
                fp = fopen(opt1,"rb");
                fread(f,99999,1,fp);
                printf("%s",f);
                fclose(fp);

                int pid = fork();
                if(pid==0)
                {
                      printf("%d\n",pid);
                      int ij = 0;
                      for(ij=0;f[ij]!='\n';ij++)
                      {
                              if(islower(f[ij]))
                              {
                                      f[ij] = toupper(f[ij]);
                              }
                      }  
                      fp = fopen("new.txt","a");
                        fprintf(fp,"\n%d   %s",pid,f);
                        fclose(fp);

                }
                else
                {
                      //printf("%s\n",f);  

                      int ij = 0;
                      for(ij=0;f[ij]!='\0';ij++)
                      {
                              if(f[ij]>='a'&&f[ij]<='z')
                                        f[ij] = f[ij] - 'a' + '0';

                      }  
                      printf("%s\n",f);  
                       fp = fopen("new.txt","a");
                        fprintf(fp,"\n%d   %s",pid,f);
                         fclose(fp);
                 }
               

                strcpy(opt1,"done");
                send(ns,opt1,sizeof(opt1),0);

        
        close(ns);
        close(s);
}

