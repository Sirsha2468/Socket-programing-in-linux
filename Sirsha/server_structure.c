#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
int roll;
char name[40];
float cgpa;
}RECORD;

typedef struct
{
int rec_no;
int roll;
char name[40];
float cgpa;
}R_RECORD;

int main()
{
   int server_sockfd, client_sockfd;
   int server_len, client_len;
   int req_no=0;
   RECORD buf;
   R_RECORD reco;
   
   struct sockaddr_un server_address;
   struct sockaddr_un client_address;
   unlink("server_socket");
   server_sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   server_address.sun_family = AF_UNIX;
   strcpy(server_address.sun_path, "server_socket");
   server_len = sizeof(server_address);
   bind(server_sockfd, (struct sockaddr *)&server_address, server_len);
   listen(server_sockfd, 5);
   
   while(1) {
      req_no++; 
      printf("server waiting\n:");
      client_len = sizeof(client_address);
      client_sockfd = accept(server_sockfd,(struct sockaddr *)&client_address, &client_len);
      read(client_sockfd, &buf, sizeof(buf));

      reco.rec_no=req_no;
      reco.roll=buf.roll;
      strcpy(reco.name,buf.name);
      reco.cgpa=buf.cgpa;

      write(client_sockfd, &reco, sizeof(reco));
      close(client_sockfd);
   }
}
