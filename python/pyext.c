//gcc  -ID:\Python26\include pyext.c -o  pyext.o 
//gcc -c  -fpic  -ID:\Python27\include pyext.c -o  pyext.o D:\Python27\libs\libpython27.a
//gcc -shared  -ID:\Python27\include pyext.c -o  pyext.o D:\Python27\libs\libpython27.a
//gcc -shared  -ID:\Python27\include pyext.c -o  pyext.dll D:\Python27\libs\libpython27.a


//python setup.py build

//import pyext
//pyext.echo("hello")

#include "Python.h"

#include <stdio.h>


char* echo(char* ch)
{
  return ch;
}


int add(int a, int b)
{
  return a+b;
}
/* int main() */
/* { */
/*   printH(); */
/* } */
  


static PyObject* pyext_echo(PyObject* self, PyObject* args)
{
  char* orig_str;
  PyObject* retval;
  if( !PyArg_ParseTuple(args, "s", &orig_str) )
    {
      return NULL;
    }

  retval =  (PyObject*)Py_BuildValue( "s", echo(orig_str) );
  return retval;
}


static PyObject* pyext_add(PyObject* self, PyObject* args) //1, PyObject* args2)
{
  int a, b, ret;
  PyObject* retval;


  if( !PyArg_ParseTuple(args, "ii", &a, &b) )
    {
      return NULL;
    }

  
  /* if( !PyArg_ParseTuple(args1, "i", &a) ) */
  /*   { */
  /*     return NULL; */
  /*   } */


  /* if( !PyArg_ParseTuple(args2, "i", &b) ) */
  /*   { */
  /*     return NULL; */
  /*   } */

  
  ret = add(a, b);
  retval =  (PyObject*)Py_BuildValue( "i", ret );
  return retval;
}






static PyMethodDef pyextMethods[] = {
  {"echo", pyext_echo, METH_VARARGS},
  {"add", pyext_add, METH_VARARGS},
  {NULL, NULL}
};


void initpyext(void)
{
  Py_InitModule("pyext", pyextMethods); 
}
  
