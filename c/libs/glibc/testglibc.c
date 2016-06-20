//g++ testglibc.c -o testglibc.linux
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <unistd.h>

#include <time.h>


#include <execinfo.h>

int main(int argc, char* argv[]) {

    clock_t begin = clock();
    printf("%s\n", program_invocation_name); //GNU extensions
    printf("%s\n", program_invocation_short_name); //GNU extensions

    fprintf(stdout, "jack\n");
    fprintf(stdout, "ttyname:%s\n", ttyname(stdout->_fileno));

    clock_t end = clock();
    /* printf("cpu tick eclipse:%d\n", (long double)(end-begin)); */
    /* printf("cpu eclipse:%d\n", ((long double)(end-begin))/CLOCKS_PER_SEC); */
    printf("CLOCKS_PER_SEC :%d\n", CLOCKS_PER_SEC);


    void* backbuff[10];
    int numret = backtrace(backbuff, 10);
    printf("numret:%d\n", numret);
    char** ppchar = backtrace_symbols(backbuff, numret);
    for(int i=0; i<numret; ++i) {
        printf("i:%d %s\n", i, ppchar[i]);
    }
    

    printf("i know printf is line buffered    ");
    printf("write ptr diff:%d               ", stdout->_IO_write_end-stdout->_IO_write_base);
    printf("read ptr diff:%d               ", stdout->_IO_read_end-stdout->_IO_read_base);
    printf("buf ptr diff:%d               ", stdout->_IO_buf_end-stdout->_IO_buf_base);
    printf("stdout _fileno:%d               ", stdout->_fileno);
    return EXIT_SUCCESS;
}
