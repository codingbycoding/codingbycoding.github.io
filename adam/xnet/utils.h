#ifndef ADAM_XNET_UTILS_H_
#define ADAM_XNET_UTILS_H_

#include <errno.h>
#include <stdio.h>


#define RT_ERR(ret_val)							\
	print_err();								\
	return ret_val;

int print_err() {
	char errbuf[1024];
	if(!strerror_r(errno, errbuf, sizeof(errbuf))) {
		printf("socket %s\n", errbuf);
	}
}

#endif
