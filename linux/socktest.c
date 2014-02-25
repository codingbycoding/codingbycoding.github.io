//gcc socktest.c -o sockettest.linux

#include <stdio.h>
#include <arpa/inet.h>


int main() {

  char* addr1 = inet_ntoa("127.0.0.1");
  char* addr2 = inet_ntoa("127.0.0.111");

  printf("%s\n%s\n", addr1, addr2);
  
}
