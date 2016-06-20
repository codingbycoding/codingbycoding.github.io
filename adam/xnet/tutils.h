#ifndef ADAM_XNET_TUTILS_H_
#define ADAM_XNET_TUTILS_H_

#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>
#include <sys/socket.h>
#include <netinet/in.h>


int setnonblock(int fd) {
	int fd_flag = fcntl(fd, F_GETFD);
	if(-1 == fd_flag) {		

		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("fcntl F_GETFD %s\n", errbuf);
		}
		
		return -1;
	}
		
	long new_fd_flag = O_NONBLOCK | fd_flag;		
	int ret = fcntl(fd, F_SETFD, new_fd_flag);

	if(-1 == ret) {
		
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("fcntl F_GETFD %s\n", errbuf);
		}

	}

	return ret;
}

int tcp_sk(uint16_t port) {
	int skfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == skfd) {
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("socket %s\n", errbuf);
		}

		return -1;
	}

	struct sockaddr_in skaddr_in;
	skaddr_in.sin_family = AF_INET;
	skaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);	
	skaddr_in.sin_port = htons(port);	

	if(-1 == bind(skfd, (struct sockaddr*)&skaddr_in, sizeof(struct sockaddr))) {
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("socket %s\n", errbuf);
		}
	}

	if(0 != setnonblock(skfd)) {
		return -1;
	}
	
	return skfd;
}

int tcp_serv_sk(uint16_t port, uint32_t backlog) {
	int skfd = socket(AF_INET, SOCK_STREAM, 0);
	if(-1 == skfd) {
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("socket %s\n", errbuf);
		}

		return -1;
	}

	struct sockaddr_in skaddr_in;
	skaddr_in.sin_family = AF_INET;
	skaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);	
	skaddr_in.sin_port = htons(port);	

	int option_value = 1;
	if(-1 == setsockopt(skfd, SOL_SOCKET, SO_REUSEADDR, (void*)&option_value, sizeof(option_value))) {
		return -1;
	}
	
	if(-1 == bind(skfd, (struct sockaddr*)&skaddr_in, sizeof(struct sockaddr))) {
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("socket %s\n", errbuf);
		}
	}

	if(0 != setnonblock(skfd)) {
		return -1;
	}

	if(-1 == listen(skfd, backlog)) {
		return -1;
	}
	
	return skfd;
}

/* int tcpsocket(const char* host, uint16_t port) { */
/* 	sockaddr_in skaddr_in; */
/* 	skaddr_in.sin_family = AF_INET; */
/* 	skaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);	 */
/* 	skaddr_in.sin_port = htons(port);	 */
	
/* 	return 0; */
/* } */

#endif	
