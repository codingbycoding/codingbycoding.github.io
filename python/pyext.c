//gcc  -ID:\Python26\include pyext.c -o  pyext.o

#include "Python.h"

#include <stdio.h>

void printH()
{
  printf("HelloWorld\n");
}



int main()
{
  printH();
}
  


static PyObject* pyext_printH(PyObject* self, PyObject* args)
{
  printH();
}


static PyMethodDef pyextMethods[] = {
  {"printH", "pyext_printH", METH_NOARGS},
  {NULL, NULL}
}


  void initpyext()
  {
    Py_InitModule("pyext", pyextMethods); 
  }
  
