//gcc  -ID:\Python26\include crunpy.c -o  crunpy.exe D:\Python26\libs\libpython26.a

//gcc  -ID:\Python27\include crunpy.c -o  crunpy.exe D:\Python27\libs\libpython27.a


#include "Python.h"


#include <stdio.h>


int main()
{
  Py_Initialize();
  PyRun_SimpleString("print 'hi'");
  PyRun_SimpleString("import sys; print sys.platform");  
  Py_Finalize();
  printf("HelloWorld.\n");
  return 0;
}
