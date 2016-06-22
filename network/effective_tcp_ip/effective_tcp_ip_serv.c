//gcc effective_tcp_ip_serv.c utils.c -o effective_tcp_ip_serv.linux 
//gcc command should tell struct keyword explicitly


//gcc -c effective_tcp_ip.cpp -o effective_tcp_ip.o //static lib
//ar -a effective_tcp_ip.a effective_tcp_ip.o

//gcc effective_tcp_ip.cpp -fPIC -shared -o effective_tcp_ip.so //dynamic lib 


//prevent to use read and write function on a socket because Win32 API socket don't support.

#include <sys/epoll.h>
#include <stdbool.h>
#include <errno.h>

#include "effective_tcp_ip_header.h"
#include "utils.h"


int main(int argc, char** argv) {

	struct sockaddr_in local_addr; //gcc should tell struct keyword explicitly
	local_addr.sin_family = AF_INET;
	local_addr.sin_port = htons(kServPort);
	local_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	if(sockfd < 0) {
		return ERR_SOCK_INIT;
	}

	if(bind(sockfd, (struct sockaddr*)&local_addr, sizeof(local_addr)) < 0) {
		return ERR_SOCK_BIND;
	}

	if(listen(sockfd, kBacklog) < 0) {
		return ERR_SOCK_LISTEN;
	}

	int epfd = epoll_create(kEpollSize);
	if(epfd < 0) {
		return ERR_EP_CREATE;
	}

	struct epoll_event event;
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = sockfd;
	int ctl_ret = epoll_ctl(epfd, EPOLL_CTL_ADD, sockfd, &event);
	if(ctl_ret < 0) {
		return ERR_EP_ADD;
	}

	struct epoll_event wait_events[kEpollSize];
	int n_wait = 0;
	do {
		n_wait = epoll_wait(epfd, wait_events, kEpollSize, 0);
		if(n_wait < 0) {
			return ERR_EP_WAIT;
		}
		
		if(0 == n_wait) {
			continue;
		}

		while(n_wait--) {
			if(wait_events[n_wait].events & EPOLLIN) {
				if(wait_events[n_wait].data.fd == sockfd) { //listen sock new accept
					struct sockaddr_in peer_addr;
					socklen_t peer_addr_len;
					int peer_sockfd = accept(sockfd, (struct sockaddr*)&peer_addr, &peer_addr_len);
					if(peer_sockfd < 0) {
						return ERR_SOCK_ACCEPT;
					}

					if(setnonblock(peer_sockfd) < 0) {
						printf("setnonblock ERR\n");
					}
				
					struct epoll_event event;
					event.events = EPOLLIN | EPOLLET;
					event.data.fd = peer_sockfd;
					int ctl_ret = epoll_ctl(epfd, EPOLL_CTL_ADD, peer_sockfd, &event);
					if(ctl_ret < 0) {
						printf("ERR_EP_ADD peer_sockfd:%d\n", peer_sockfd);
					}
					
					continue; //new accept socket handle finished.
				}

				//handle connected sock
				char recv_buf[kRecvBufSize];
				int recv_len = recv(wait_events[n_wait].data.fd, recv_buf, kRecvBufSize, 0);
				if(recv_len < 0) {
					if(EAGAIN == errno || EWOULDBLOCK == errno) {
						printf("socket recv EAGAIN");					
						continue;
					}
					
					perror("ERR_SOCK_RECV");
					printf("ERR_SOCK_RECV peer_sockfd:%d ", wait_events[n_wait].data.fd);					
					continue;
				}

				if(0 == recv_len) {
					int ctl_ret = epoll_ctl(epfd, EPOLL_CTL_DEL, wait_events[n_wait].data.fd, &wait_events[n_wait]);
					if(ctl_ret < 0) {
						printf("ERR_EP_DEL peer_sockfd:%d\n", wait_events[n_wait].data.fd);
					}
					continue; //peer closed
				}

				recv_buf[recv_len] = '\0';
				printf("recv_buf:%s\n", recv_buf);			
			}
		
		}
	} while(true); //epoll_wait loop

	
	printf("Run to the final.\n");
	return EXIT_SUCCESS;
}
