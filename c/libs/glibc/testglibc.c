//g++ testglibc.c -o testglibc.linux
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char* argv[]) {

    printf("%s\n", program_invocation_name); //GNU extensions

    printf("%s\n", program_invocation_short_name); //GNU extensions
    
    return EXIT_SUCCESS;
}
