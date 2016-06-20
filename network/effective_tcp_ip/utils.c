#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>


#include "utils.h"



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
