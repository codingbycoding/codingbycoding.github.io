//gcc  -ID:\Python26\include crunpy.c -o  crunpy.exe D:\Python26\libs\libpython26.a
#include "Python.h"


#include <stdio.h>


int main()
{
  Py_Initialize();
  PyRun_SimpleString("print 'hi'");
  Py_Finalize();
  printf("HelloWorld.\n");
  return 0;
}
