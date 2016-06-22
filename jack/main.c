//g++ -ggdb main.c -I~/Documents/libs/libevent-1.4.14b-stable/ -I/home/adam/test/strike2014/server/proto/client -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/  -L~/Documents/libs/libevent-1.4.14b-stable/build/.libs -lprotobuf -lclientproto -levent -o main.linux

#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <fcntl.h>

#include <errno.h>

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <map>

#include <event.h>


#include "pb0x01.pb.h"
#include "header.pb.h"

struct cli_proto_header_t
{
    uint32_t total_len;
    uint16_t head_len;
    uint16_t cmd;
} __attribute__((packed));



void c_peer_cb_op(int fd, short events, void* arg);
	
int c_setnonblock(int fd) {
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

class TTcpAcceptor {
 public:
 TTcpAcceptor() : event_(NULL) {
		fd_ = socket(AF_INET, SOCK_STREAM, 0);
		if(-1 == fd_) {
			std::cerr <<  "socoket errno:" << errno << std::endl;
		}

		/* struct sockaddr_in { */
        /*        sa_family_t    sin_family; /\* address family: AF_INET *\/ */
        /*        in_port_t      sin_port;   /\* port in network byte order *\/ */
        /*        struct in_addr sin_addr;   /\* internet address *\/ */
        /*    }; */


		sockaddr_in skaddr_in;
		skaddr_in.sin_family = AF_INET;
		skaddr_in.sin_port = htons(8989);
		//skaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
		skaddr_in.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

		memcpy(&sockaddr_, &skaddr_in, sizeof(sockaddr_));
		
		if(-1 == bind(fd_, &sockaddr_, sizeof(sockaddr_))) {
			std::cerr << "bind errno:" << errno << std::endl;
		}

		/* ioctl(fd_, ) */

		/* setsockopt(fd_, SO_); */
		if(-1 == listen(fd_, 1024)) {
			
		}

		if(c_setnonblock(fd_)) {
			std::cerr << "setnonblock err" << std::endl;
		}
		
				
		//int fcntl(int fd, int cmd, ... /* arg */ );

		//global /proc/sys/net/ipv4/tcp_wmem
		//global /proc/sys/net/ipv4/tcp_rmem

		///proc/sys/net/core/wmem_max
		///proc/sys/net/core/rmem_max

		//On individual  connections, the socket buffer size must be set prior to       the listen(2) or connect(2) calls in order to have it  take  effect.       See socket(7) for more information.

		//zero-copy sendfile(2)

		
		//EPIPE  The  other  end  closed  the socket unexpectedly or a read is              executed on a shut down socket.

		//ETIMEDOUT The other end didn’t  acknowledge  retransmitted  data  after             some time.

		/* SO_SNDBUF; */
		/* SO_RCVBUF; */
		/* setsockopt; */
	}
	
	~TTcpAcceptor() {
		
	}

	void cb_op(int fd, short events, void* arg) {
		std::cout << __func__ << std::endl;
		sockaddr peer_sockaddr;
		socklen_t addrlen;
		int peer_fd = accept(fd_, &peer_sockaddr, &addrlen);
		if(-1 == peer_fd) {
			std::cerr << "peer_fd errno:" << errno << std::endl;
			
		} else {
			c_setnonblock(peer_fd);
			event* ev = new event;
			//event_set(ev, peer_fd, EV_READ|EV_WRITE, c_peer_cb_op, (void*)this);
			event_set(ev, peer_fd, EV_READ, c_peer_cb_op, (void*)this);
			peer_ev_[peer_fd] = ev;
			event_add(ev, NULL);
		}

		event_add(event_, NULL);
	}
	
	int get_fd() {
		return fd_;
	}

	void peer_cb_op(int fd, short events, void* arg) {
		std::cout << __func__ << std::endl;
		
		std::map<uint32_t, event*>::iterator it = peer_ev_.find(fd);

		
		if((peer_ev_.end() != it) && (EV_READ & events)) {
			const int bufsize = 1024;
			char buf[bufsize];
			//int rd_len = read(fd, buf, bufsize-1);
			int rd_len;
			do {
				rd_len = recv(fd, buf, bufsize-1, 0);
				if(0 < rd_len) {
					/* buf[rd_len] = '\0'; */
					/* std::cout << "rd_len:" << rd_len << " buf:\"" << buf << "\"" << std::endl; */
					if(8 < rd_len) {
						cli_proto_header_t* header = (cli_proto_header_t*)buf;

						onlineproto::proto_header_t proto_header;
						proto_header.ParseFromArray(buf+8, header->head_len);
						std::cout << proto_header.DebugString() << std::endl;
						
						switch(header->cmd) {
						case 0x0101:
							{
								onlineproto::cs_0x0101_enter_svr enter_svr;
								enter_svr.ParseFromArray(buf+8+header->head_len, header->total_len-8-header->head_len);
								std::cout << enter_svr.DebugString() << std::endl;
							}
							break;
								
						case 0x0125:
							{
								onlineproto::cs_0x0125_buy_diamond buy_diamond;
								buy_diamond.ParseFromArray(buf+8+header->head_len, header->total_len-8-header->head_len);
								std::cout << buy_diamond.DebugString() << std::endl;
							}
							break;
						}
						
						
					}
					
				}
			} while(rd_len > 0);
				
			if(0 == rd_len) {
				close(fd);
				delete it->second;
				peer_ev_.erase(fd);
				std::cout << "close(fd)" << std::endl;
				return;				
			}
			
			if(-1 == rd_len && (errno == EAGAIN || errno == EWOULDBLOCK)) {
				std::cout << "(errno == EAGAIN || errno == EWOULDBLOCK)" << std::endl;
			}
			
			
			event_add(it->second, NULL);
		}

		
	}
		
	event* set_event(event* ev) {
		event_ = ev;
		return get_event();
	}
	
	event* get_event() {
		return event_;
	}
	
 private:
	int fd_;
	event* event_;
	/* socket sock_; */
	sockaddr sockaddr_;

	std::map<uint32_t, event*> peer_ev_;
	
};


void c_cb_op(int fd, short events, void* arg) {
	TTcpAcceptor* pTcpAcceptor = (TTcpAcceptor*)arg;
	pTcpAcceptor->cb_op(fd, events, arg);
}

void c_peer_cb_op(int fd, short events, void* arg) {
	TTcpAcceptor* pTcpAcceptor = (TTcpAcceptor*)arg;
	pTcpAcceptor->peer_cb_op(fd, events, arg);	
}


int main(int argc, char* argv[]) {

	TTcpAcceptor tcpAcceptor;
	
	
	event_base* ev_base = event_init();

	std::cout << "event_base_get_method:" << event_base_get_method(ev_base) << std::endl;
	/* typedef struct dummy_data_t { */
	/* 	int x; */
	/* 	int y; */
	/* } dummy_data_t; */

	/* dummy_data_t dummy_data;*/

	/* event_set(struct event *ev, int fd, short events, void (*callback)(int, short, void *), void *arg); */
	event ev;
	event_set(&ev, tcpAcceptor.get_fd(), EV_READ, c_cb_op, (void*)&tcpAcceptor);
	tcpAcceptor.set_event(&ev);
	event_add(&ev, NULL);
	int ret =  event_dispatch();
	return ret ? ret : EXIT_SUCCESS;
}
