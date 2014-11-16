//gcc xnet.c -o xnet
//gcc -std=gnu89 xnet.c -o xnet

#include <stdio.h>
#include <stdlib.h>

#include <unistd.h>


int main(int argc, char* argv[]) {

#ifdef __USE_GNU 	
	printf("__USE_GNU:%d", __USE_GNU);
#endif	
	
	printf("%s\n", argv[0]);
	return EXIT_SUCCESS;
}
