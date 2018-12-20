#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netdb.h>
#include<errno.h>
 
#define PORT 8888
#define MAX_MSG_SIZE 1024
 
int main(void)
{
   int sockfd, addrlen, n;
   struct sockaddr_in addr;
   char msg[MAX_MSG_SIZE];
   sockfd = socket(AF_INET, SOCK_DGRAM, 0);
   if (sockfd < 0)
   {
      fprintf(stderr, "socket failed\n");
      exit(EXIT_FAILURE);
   }
   addrlen = sizeof(struct sockaddr_in);
   bzero(&addr, addrlen);
   addr.sin_family = AF_INET;
   addr.sin_addr.s_addr = htonl(INADDR_ANY);
   addr.sin_port = htons(PORT);
   if (bind(sockfd, (struct sockaddr*)(&addr), addrlen) < 0)
   {
      fprintf(stderr, "bind fail\n");
      exit(EXIT_FAILURE);
   }
   puts("bind success");
   while (1)
   {
      bzero(msg, MAX_MSG_SIZE);
      n = recvfrom(sockfd, msg, sizeof(msg), 0, (struct sockaddr *)(&addr), &addrlen);
      fprintf(stdout, "Recevie message from client is %s\n", msg);
      fgets(msg, MAX_MSG_SIZE,stdin);
      printf("Server endpoint input message %s\n", msg);
      sendto(sockfd, msg, n, 0,(struct sockaddr *)(&addr), addrlen);
   }
   close(sockfd);
   exit(EXIT_SUCCESS);
}
