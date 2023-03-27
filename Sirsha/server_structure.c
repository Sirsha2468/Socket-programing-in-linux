#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

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
   int sockfd;
   int len;
   char ch;
   RECORD s_reco;
   R_RECORD r_reco;
   struct sockaddr_un address;
   int result;
   
   printf("\n Enter the Roll No.:");
   scanf("%d",&s_reco.roll);
   scanf("%c",&ch);
   printf("\n Enter the Name:");
   scanf("%[^\n]s",s_reco.name);
   scanf("%c",&ch);
   printf("\n Enter the CGPA:");
   scanf("%f",&s_reco.cgpa);
 
   sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
   address.sun_family = AF_UNIX;
   strcpy(address.sun_path, "server_socket");
   len = sizeof(address);
   result = connect(sockfd, (struct sockaddr *)&address, len);
   if(result == -1) {
      perror("oops: client1");
      exit(1);
   }
   write(sockfd, &s_reco, sizeof(s_reco));
   read(sockfd, &r_reco, sizeof(r_reco));
   printf("Record received from the server : \n Record No. %d \n %d, %s, %.2f\n",r_reco.rec_no, r_reco.roll, r_reco.name, r_reco.cgpa);
   close(sockfd);
   exit(0);
}
