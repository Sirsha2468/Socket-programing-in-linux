#include<sys/types.h>
#include<sys/socket.h>
#include<stdio.h>
#include<sys/un.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>

int main()
{
int sockfd;
int len;
struct sockaddr_un address;
int result;
//char ch = 'A';
char name[20]="Sirsha";
char r_str[40];

sockfd = socket(AF_UNIX, SOCK_STREAM, 0);
address.sun_family = AF_UNIX;
strcpy(address.sun_path, "server_socket");
len = sizeof(address);
result = connect(sockfd, (struct sockaddr *)&address, len);
if(result == -1) {
perror("oops: client1");
exit(1);
}
//write(sockfd, &ch, 1);
//read(sockfd, &ch, 1);

write(sockfd,name,strlen(name)+1);
read(sockfd,r_str,sizeof(r_str));

printf("String from server = %s\n", r_str);
close(sockfd);
exit(0);
}


