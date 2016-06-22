//gcc socktest.c -o sockettest.linux

#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <sys/epoll.h>

#include <stdbool.h>

#include <fcntl.h>

#include <signal.h>
#include <errno.h>

#include <stdlib.h>


struct sock_server_t {
  int ss_;  
  struct sockaddr_in servaddr_;
};


struct sock_server_t g_sock_server;

int sock_server_create() {
  g_sock_server.ss_ = socket(AF_INET, SOCK_STREAM, 0);
  if(g_sock_server.ss_ == -1) {
    perror("sockdf error\n");
  }

  bzero(&(g_sock_server.servaddr_), sizeof(g_sock_server.servaddr_));
  g_sock_server.servaddr_.sin_family = AF_INET;
  g_sock_server.servaddr_.sin_port = htons(2014);
  if( inet_pton(AF_INET, "127.0.0.1", &(g_sock_server.servaddr_.sin_addr)) != 1)
    {
      perror("inet_pton error\n");
    }

  if( bind(g_sock_server.ss_, (struct sockaddr*)&(g_sock_server.servaddr_), sizeof(g_sock_server.servaddr_)) != 0)
    {
      perror("bind error\n");
    }

  if(0 != listen(g_sock_server.ss_, 64)) {
    perror("listen");
  }
  
  return 0;
}
  

enum {MAX_EVENTS = 1024};

bool g_bstop = false;

void sigaction_handle_fun(int signo, siginfo_t* info, void* sigcontext ) {
  printf("sigaction_handle_fun\n");
  g_bstop = true;
}

int main() {

  sock_server_create();
  int epollfd, nfds;
  struct epoll_event ev, events[MAX_EVENTS];


  struct sockaddr_in addr;
  int addrlen = sizeof(addr); 
  int newconn;

  
  if( -1 == (epollfd = epoll_create(MAX_EVENTS)) ) {
    perror("epoll_create failed");
  }

  ev.events = EPOLLIN;
  ev.data.fd = g_sock_server.ss_;

  if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, g_sock_server.ss_, &ev)) {
    perror("epoll_ctl failed.");
  }


  struct sigaction act, oact;
  sigemptyset(&act.sa_mask);
  act.sa_flags = SA_SIGINFO;
  act.sa_sigaction = sigaction_handle_fun;
  sigaction(SIGTERM, &act, &oact);

  	int recvlen = 0;
	
  while(!g_bstop) {

    if( -1 == (nfds = epoll_wait(epollfd, events, MAX_EVENTS, -1)) ) {
      if(errno == EINTR) {
	continue;
      } else {
	perror("epoll_wait failed.");
      }
      
    }

    int i=0;
    for(; i<nfds; ++i) {

      if(events[i].data.fd != g_sock_server.ss_) {
	char chbuff[1024];
	bzero(chbuff, strlen(chbuff));

	if( (recvlen = recv(events[i].data.fd, chbuff, 5, 0 )) > 0) {
        //if( (recvlen = recv(events[i].data.fd, chbuff, 1024, 0 )) > 0) {
	  printf("recv %d: %s\n", recvlen, chbuff);

	}

      } else {
	if(-1 == (newconn = accept(g_sock_server.ss_, (struct sockaddr*)&addr, &addrlen )) ) {
	  perror("accept error");
	}
	printf("accept..\n");
	  
	/* setnonblocking(newconn); */
	fcntl(newconn, F_SETFD, O_NONBLOCK);

	ev.events = EPOLLIN | EPOLLET;
	ev.data.fd = newconn;
	if(-1 == epoll_ctl(epollfd, EPOLL_CTL_ADD, newconn, &ev)) {
	  perror("epoll_ctl newconn failed");
	}

      }
    }
      
    
  }

  printf("close listened socket\n");
  shutdown(g_sock_server.ss_, SHUT_RDWR);
  //close(g_sock_server.ss_);

  return EXIT_SUCCESS;
}
