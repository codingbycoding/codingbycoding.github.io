//g++ effective_tcp_ip.cpp -o effective_tcp_ip.linux

//g++ -c effective_tcp_ip.cpp -o effective_tcp_ip.o //static lib
//ar -a effective_tcp_ip.a effective_tcp_ip.o

//g++ effective_tcp_ip.cpp -fPIC -shared -o effective_tcp_ip.so //dynamic lib 

#include <sys/socket.h>


int main(int argc, char** argv) {
	return 0;
}
