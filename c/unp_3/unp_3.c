//gcc unp_3.c -o unp_3.linux

#include <stdio.h>
#include <strings.h>
#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>

int main(int argc, char* argv[])
{
  printf("%s is running...\n", argv[0]);

  int servsock;
  struct sockaddr_in servaddr;
  #define SERVPORT 10000
  
  if( (servsock = socket(AF_INET, SOCK_STREAM, 0)) == -1)
  {
    perror("socket error\n");
    return -1;
  }

  bzero(&servaddr, sizeof(servaddr));
  servaddr.sin_family = AF_INET;
  servaddr.sin_port = htons(SERVPORT);
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);

  if( listen(servsock, 16) == -1)
    {
      perror("listen error\n");
      return -1;
    }
  
  
  return 0;
}
