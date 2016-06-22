//gcc xnet.c -o xnet
//gcc -std=gnu99  xnet.c -o xnetb


#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>

#include <sys/epoll.h>

#include "tutils.h"
#include "utils.h"
#include "header.h"

#define MAX_CLIENT_NUM 50000 //最大可处理的玩家连接数量-5(0, 1, 2, 3, 4)(standard nput , standard out, standard error, epoll_fd, listen_fd)

#define SVR_PORT 9999

#define MAX_EVENTS 20000

int main(int argc, char* argv[]) {

#ifdef __USE_GNU 	
	printf("__USE_GNU:%d", __USE_GNU);
#endif	
	
	printf("%s\n", argv[0]);

	int epfd = epoll_create(MAX_CLIENT_NUM);
	if(-1 == epfd) {
		char errbuf[1024];
		if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
			printf("socket %s\n", errbuf);
		}

		return -1;
	}

	int tcp_serv_fd = tcp_serv_sk(SVR_PORT, 20000);
	if(0 >= tcp_serv_fd) {
		RT_ERR(-1);
	}
	
	struct epoll_event event;
	event.events = EPOLLIN | EPOLLET;
	event.data.fd = tcp_serv_fd;
	

	if(-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, tcp_serv_fd, &event)) {
		RT_ERR(-1);
	}

	struct epoll_event events[MAX_EVENTS];

	int ret_n;
	while(-1 != (ret_n = epoll_wait(epfd, events, MAX_EVENTS, 0))) {
		while(ret_n) {
			--ret_n;
			if(tcp_serv_fd == events[ret_n].data.fd) {
				struct sockaddr peeraddr;
				socklen_t addrlen = sizeof(peeraddr);
				int fd_ret = accept(events[ret_n].data.fd, &peeraddr, &addrlen);
				if(-1 == fd_ret) {
					RT_ERR(-1);
				}

				setnonblock(fd_ret);

				struct epoll_event event;
				event.events = EPOLLIN | EPOLLET;
				event.data.fd = fd_ret;
				if(-1 == epoll_ctl(epfd, EPOLL_CTL_ADD, fd_ret, &event)) {
					RT_ERR(-1);
				}
				
			} else if(events[ret_n].events & EPOLLRDHUP) {
				printf("EPOLLRDHUP fd:%u closed\n", events[ret_n].data.fd);
				
			} else if(events[ret_n].events & EPOLLHUP) {
				printf("EPOLLHUP fd:%u closed\n", events[ret_n].data.fd);
				
			} else {
				
				char headerbuf[sizeof(header_t)];
				memset(headerbuf, 0, sizeof(headerbuf));
				int ret_rd = 0;
				int rd_sum = 0;
				do {
					ret_rd = read(events[ret_n].data.fd, headerbuf+rd_sum, sizeof(headerbuf));
					rd_sum += ret_rd;
				} while(ret_rd > 0 && ret_rd < sizeof(headerbuf));

				if(-1 == ret_rd) {
					if(EAGAIN == errno || EWOULDBLOCK == errno) {
						//TODO.
					}
				}
				
				if(ret_rd < 0) {
					RT_ERR(-1);
				} else if(0 == ret_rd) {
					printf("fd:%u closed\n", events[ret_n].data.fd);
					continue;
				}

				uint32_t len = ntohl(*(uint32_t*)headerbuf);
				printf("len:%u\n", len);
				
				if(len > 1024) {
					printf("len:%u overflow\n", len);
					continue;
				}
				
				char buf[1024];
				memset(buf, 0, sizeof(buf));
				rd_sum = 0;
				do {
					ret_rd = read(events[ret_n].data.fd, buf+rd_sum, sizeof(buf));
					rd_sum += ret_rd;
				} while(ret_rd >0 && ret_rd < len);

				if(ret_rd < 0) {
					RT_ERR(-1);
				} else if(0 == ret_rd) {
					printf("fd:%u closed\n", events[ret_n].data.fd);
					continue;
				}

				printf("buf:%s\n", buf);
				
			}
		
			printf("events fd:%u\n", events[ret_n].data.fd);
		}
	}

	if(-1 == ret_n) {
		RT_ERR(-1);
	}
	
	return EXIT_SUCCESS;
}
