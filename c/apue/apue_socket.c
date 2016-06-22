//gcc apue_socket.c -o apue_socket.linux

#include <stdio.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <string.h>


int main(int argc, char* argv[])
{
  printf("Program %s is running...\n", argv[0]);
  if(argc != 2)
    {
      printf("not input param\n");
      return -1;
    }

  int sockdf = socket(AF_INET, SOCK_STREAM, 0);
  if(sockdf == -1)
    perror("sockdf error\n");

  struct sockaddr_in servaddr;
  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(80);
  if( inet_pton(AF_INET, argv[1], &servaddr.sin_addr) != 1)
    {
      perror("inet_pton error\n");
    }

  if( connect(sockdf, (struct sockaddr*)&servaddr, sizeof(servaddr)) != 0)
    {
      perror("connect error\n");
    }

  
  
  /* char* hostname; */
  /* int nlen = malloc(HOST_NAME_MAX); */
  /* gethostname(hostname, nlen); */
  /* getaddrinfo(hostname,  */

	  
  /* if(shutdown(sockdf, SHUT_RD) == -1) */
  /*   perror("shutdown error\n"); */

  if(close(sockdf) == -1)
    perror("close error\n");

  setservent(1);
  struct servent* ser = getservbyport(13, NULL);
  if(ser != NULL)
    {
      printf("ser->s_name %s\n", ser->s_name);
    }
  else
    {
      perror("ser error\n");
    }
  endservent();
  return 0;
}
