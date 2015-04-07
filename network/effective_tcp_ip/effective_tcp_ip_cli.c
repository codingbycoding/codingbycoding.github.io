//gcc effective_tcp_ip_cli.c -o effective_tcp_ip_cli.linux

//gcc -c effective_tcp_ip.cpp -o effective_tcp_ip.o //static lib
//ar -a effective_tcp_ip.a effective_tcp_ip.o

//gcc effective_tcp_ip.cpp -fPIC -shared -o effective_tcp_ip.so //dynamic lib 


//prevent to use read and write function on a socket because Win32 API socket don't support.


#include <string.h>
#include <wchar.h>
#include <locale.h>

#include "effective_tcp_ip_header.h"


int main(int argc, char** argv) {

	wchar_t* w_buf = L"中文";
	setlocale(LC_ALL, "zh_CN.UTF-8");
	wprintf(L"w_buf:%ls wcslen:%d byte:%d\n", w_buf,  wcslen(w_buf), wcslen(w_buf)*sizeof(wchar_t));
	char* buf = "中文";
	printf("buf:%s size:%d\n", buf,  strlen(buf));
	//wprintf(L"buf:%s size:%d\n", buf,  strlen(buf));

	
	
	struct sockaddr_in serv_addr;
	serv_addr.sin_family = AF_INET;
	serv_addr.sin_port = htons(kServPort);
	serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

	int sockfd = socket(AF_INET, SOCK_STREAM, 0);	
	if(sockfd < 0) {
		return ERR_SOCK_INIT;
	}

	if(connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
		return ERR_SOCK_CONN;
	}


	char* send_buf = "Hello World!";
	if(send(sockfd, send_buf, strlen(send_buf), 0) < 0) {
		return ERR_SOCK_SEND;
	}




	printf("Run to the final.\n");
	return EXIT_SUCCESS;
}
