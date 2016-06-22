#include <sys/socket.h>
#include <stdio.h>
#include <netinet/in.h>
#include <string.h>

int main()
{
	int socket_fd; 
	
	printf("Client ...\n");	

	if( (socket_fd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) 
	{
		printf("Error socket failed!\n");	
		return -1;
	}	


	struct sockaddr_in cli_addr;
	struct sockaddr_in dest_addr;
	memset(&cli_addr, 0, sizeof(struct sockaddr_in) );
	memset(&dest_addr, 0, sizeof(struct sockaddr_in) );
	
	dest_addr.sin_port = htons(10030);
	/*
	if( inet_pton(AF_INET, "127.0.0.1", &(dest_addr.sin_addr.s_addr)) <= 0 ) 
	{
		printf("Error dest_addr inet_pton\n");	
		return -1;
	}
	*/	

	dest_addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);
	char send_buf[1024];
	//char* send_buf;
	memset(&send_buf, 0, 1024);
	strncpy(send_buf, "Hello, Serv. I'm Cli\n", sizeof("Hello, Serv. I'm Cli\n"));
			
	int send_len;
	if( sendto(socket_fd, &send_buf, sizeof("Hello, Serv. I'm Cli\n"), 0, (struct sockaddr*)&dest_addr, sizeof(dest_addr) ) >=0  )
	{
		printf("sendto succeed!\n");
	}	

		
	return 0;
}
