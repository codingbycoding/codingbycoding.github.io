#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>
#include <errno.h>

int main(int argc, char* argv)
{
	int socket_fd; 
	
	printf("Tcp Server ...!\n");	

	if( (socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0 ) 
	{
		printf("Error socket failed!\n");	
		return -1;
	}	


	struct sockaddr_in serv_addr;
	memset(&serv_addr, 0, sizeof(struct sockaddr_in) );

	serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

	serv_addr.sin_port = htons(10050);
	/*
	if( INADDR_NONE == (serv_addr.sin_addr = inet_addr("127.0.0.1")) )
	{
		printf("Error inet_addr\n");	
		return -1;
	}
	*/
	/*
	if( inet_pton(AF_INET, "127.0.0.1", &(serv_addr.sin_addr)) <= 0 ) 
	{
		printf("Error inet_pton\n");	
		return -1;
	}
	*/

	if( bind(socket_fd, (struct sockaddr*)&serv_addr, sizeof(struct sockaddr)) < 0 )
	{
		printf("Error bind errno:%d\n", errno);
		return -1;
	}

	char recv_buf[1024];
	int recv_len;

	if( listen(socket_fd, 12) < 0 )
	{
		printf("listen error errno:%d\n", errno);
	}
	struct sockaddr_in addr_peer;
	socklen_t addr_peer_len = sizeof(addr_peer);
	memset(&addr_peer, 0, sizeof(struct sockaddr_in));
	int socket_fd_peer;
    if( socket_fd_peer	= accept(socket_fd, (struct sockaddr*)&addr_peer, &addr_peer_len ) < 0 ) 
	{
		printf("accept error errno:%d\n", errno);
	}

	while( recv(socket_fd_peer, &recv_buf, 1024, 0) >0 )
	{
		printf("recv recved:%s\n", recv_buf);
	}	

		
	return 0;
}
