//gcc iconvtest.c -o iconvtest.linux es

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>

#include <iconv.h>


int main(int argc, char* argv[]) {

  printf("iconvtest:\n");

  iconv_t t = iconv_open ("GBK", "ASCII");
  size_t tsize = iconv (t,  __inbuf, __inbytesleft, __outbuf, __outbytesleft);
  iconv_close (t);
 
  
  return EXIT_SUCCESS;
}

