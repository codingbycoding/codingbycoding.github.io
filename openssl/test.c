//gcc -ggdb -std=c99 test.c -o test.linux -lssl


//g++ -ggdb -std=c++0x test.c -I/home/adam/test/strike2014/server/proto/client -I/home/adam/test/strike2014/server/online/src -L/home/adam/test/strike2014/server/proto/client -L/usr/local/lib/ -L/usr/local/lib/ -lssl  -lclientproto  -lprotobuf -o test.linux

#include "pb0x01.pb.h"
#include "header.pb.h"
#include "proto.h"


#include <openssl/rc4.h>
#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


void my_encrypt(char* indata, char* outdata, long int llen) {	
	/* unsigned char key[] = { */
	/* 	"}E(BYInIiX(.YO(~" */
    /*     "ajklj/V~awN#Yyqo!<<><<<>-cK..." */
    /*     "...]lkjsdlkfjal=;,x}9nti" */
    /*     "salkfj9814#12#jkj/Q6jZ())((g" */
	/* }; */

	unsigned char key[] = {
		0xc9, 0x2a, 0x82, 0x04, 0x45, 0X00, 0xca, 0x88, 0x40, 0x10, 0x08, 0x88, 0x84, 0x00, 0x88, 0x74, 0x04, 0x20, 0x10, 0x40, 0x11, 0x02, 0x6b, 0x10, 0x20, 0x57, 0x0e, 0x1c, 0x89, 0x45, 0x2a, 0x40, 0x1d, 0x09, 0x00, 0x80, 0x2c, 0x48, 0x08, 0x48, 0x19, 0x04, 0x90, 0x81, 0x42, 0x19, 0x08, 0x8c
	};
	
	RC4_KEY rc4_key;
	RC4_set_key(&rc4_key, sizeof(key), key);	


	char* bufs[2] = {indata, outdata};
	
	for(int i=0; i<1; ++i) {
		//RC4(&rc4_key, sizeof(indata), bufs[i & 1], bufs[i+1 & 1]);
		RC4(&rc4_key, llen, (unsigned char*)bufs[i & 1], (unsigned char*)bufs[i+1 & 1]);
	}
}


int main() {
	char indata[1024] = "jack";
	char outdata[1024];

	my_encrypt(indata, outdata, sizeof(indata));


	//decrypt
	char de_outdata[1024];
	my_encrypt(outdata, de_outdata, sizeof(indata));


	int fd_ = socket(AF_INET, SOCK_STREAM, 0);
	sockaddr_in skaddr_in;
	skaddr_in.sin_family = AF_INET;
	skaddr_in.sin_port = htons(9888);
	//skaddr_in.sin_addr.s_addr = htonl(INADDR_ANY);
	skaddr_in.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

	skaddr_in.sin_addr.s_addr = inet_addr("192.168.1.116");

	sockaddr sockaddr_;
	memcpy(&sockaddr_, &skaddr_in, sizeof(sockaddr_));

	if(-1 == connect(fd_, &sockaddr_, sizeof(sockaddr_))) {
		printf("connect errno:%d\n", errno);
	}

	const int bufsize = 1024;
	char buf[bufsize];
	memset(buf, 0, sizeof(buf));
	
	cli_proto_header_t* header = (cli_proto_header_t*)buf;
	onlineproto::proto_header_t proto_header;
	proto_header.set_seque(0);
	proto_header.SerializeToArray(buf+8, proto_header.ByteSize());

	onlineproto::cs_0x0101_enter_svr enter_svr;
	enter_svr.set_uid(10008);
	enter_svr.set_version_id(0x050003);
	enter_svr.set_session("kjakljdfkj");

	header->total_len = proto_header.ByteSize() + enter_svr.ByteSize() + 8;
	header->head_len = proto_header.ByteSize();
	header->cmd = 0x0101;
	enter_svr.SerializeToArray(buf+8+header->head_len, header->total_len-8-header->head_len);
	printf("%s\n", enter_svr.DebugString().c_str());

	/* proto_header.ParseFromArray(buf+8, header->head_len); */
	printf("%s\n", proto_header.DebugString().c_str());
	char my_outdata[1024];
	my_encrypt(buf+8, my_outdata, sizeof(buf)-8);

	memcpy(buf+8, my_outdata, sizeof(buf)-8);
	send(fd_, buf, sizeof(buf), 0);
	
	return EXIT_SUCCESS;
}
