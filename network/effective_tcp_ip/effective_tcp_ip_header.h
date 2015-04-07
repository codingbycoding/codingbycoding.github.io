#ifndef EFFECTIVE_TCP_IP_HEADER_H
#define EFFECTIVE_TCP_IP_HEADER_H


#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include <stdio.h>
#include <stdlib.h>


enum {
	kServPort = 8090
};

enum {
	kBacklog = 20000
};

enum {
	kEpollSize = 30000
};

enum {
	kRecvBufSize = 65535
};

enum {
	ERR_SOCK_INIT = 101,
	ERR_SOCK_BIND = 102,
	ERR_SOCK_LISTEN = 103,
	ERR_SOCK_ACCEPT = 104,
	ERR_SOCK_CONN = 105,
	ERR_SOCK_SEND = 106,
	ERR_SOCK_RECV = 107,
	ERR_EP_CREATE = 108,
	ERR_EP_ADD = 109,
	ERR_EP_WAIT = 109,
};

#endif
