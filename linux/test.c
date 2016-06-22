//gcc test.c -o test.linux

#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <strings.h>
#include <string.h>

int main(int argc, char* argv[]) {

    int fd;
    void* pa; 
    
    if( -1 == (fd=open("test.txt", O_RDWR|O_CREAT)) ) {
        perror("open");                
    }
    
    if( MAP_FAILED == (pa=mmap(NULL, 100, PROT_WRITE, MAP_SHARED, fd, 0)) ) {
        perror("mmap");
        return EXIT_FAILURE;
    }

//char* pch = "HelloWorld!";
char pch[11];
    /* bcopy(pch, pa, 10); */
    /* memcpy(pa, pch, 10); */

memcpy(pch, pa, 10);
pch[10] = '\0';
printf("%s\n", pch);
    
    if( -1 == munmap(pa, 100) ) {
        perror("munmap");
    }
    
    if(-1 ==close(fd) ) {
        perror("close");
    }
    
    return EXIT_SUCCESS;
}
    
