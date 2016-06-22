#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv)
{
	int socket_fd; 
	
	printf("Server ...!\n");	

	if( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{
		printf("Error socket failed!\n");	
		return -1;
	}	


	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in) );

	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	serv_addr.sin_port = htons(10030);
	/*
	if( INADDR_NONE == (serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1")) )
	{
		printf("Error inet_addr\n");	
		return -1;
	}
	*/
	/*
	if( inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr.s_addr)) <= 0 ) 
	{
		printf("Error inet_pton\n");	
		return -1;
	}
	*/

	if( bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) != 0 )
	{
		printf("Error bind errno:%d\n", errno);
		return -1;
	}

	char recv_buf[1024];
	int recv_len;

	while( recvfrom(socket_fd, &recv_buf, 1024, 0, NULL, NULL) >0 )
	{
		printf("recvfrom recved:%s\n", recv_buf);
	}	

		
	return 0;
}
