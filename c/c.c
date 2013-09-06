/* gcc -ggdb c.c -o c.exe */

#include <stdio.h>
#include <stdarg.h>

myPrint(const char* fmt, ...)
{
  va_list ap;
  va_start(ap, fmt);
  printf("%s\n", fmt);
  printf("22 %d\n", *ap);
    
  va_arg(ap, int);
  printf("32 %d\n", *ap);

  char* s = NULL;
  /* s = va_arg(ap, char*); */
  /* s = va_arg(ap, int); */
  /* printf( */
  /* printf("string %s\n", ap); */
  va_end(ap);
}

/* myPrint(const char* fmt, ...) */
/* { */
/*   va_list ap; */
/*   va_start(ap, fmt); */
  
/*   va_end(ap); */
/* } */

int main()
{
  printf("HelloWorld!\n");
  myPrint("vararg %d%d%d", 22, 32, "jack");

  printf("%s\n", "abc");
}
