#include <sys/socket.h>
#include <fcntl.h>

perror
int setnonblock(int fd) {
	int fd_flag = fcntl(fd, F_GETFD);
	if(-1 == fd_flag) {
		return -1;
		std::cerr << "fcntl errno:" << errno << std::endl;
	}
		
	fd_flag |= O_NONBLOCK;		
	fd_flag = fcntl(fd, F_SETFD, fd_flag);

	if(-1 == fd_flag) {
		return -1;
		std::cerr << "fcntl errno:" << errno << std::endl;
	}

	return 0;
}
