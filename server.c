#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
int main()
{
//int count_req=0;
int server_sockfd, client_sockfd;
int server_len, client_len;
char r_str[40];

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
char ch;
printf("server waiting\n");
client_len = sizeof(client_address);
client_sockfd = accept(server_sockfd,
(struct sockaddr *)&client_address, &client_len);

strcpy(r_str,"Hello ");
read(client_sockfd, r_str+strlen("Hello "), sizeof(r_str));
//ch=ch+(char)count_req;
//count_req++;

write(client_sockfd, r_str, sizeof(r_str));
close(client_sockfd);
}
}
