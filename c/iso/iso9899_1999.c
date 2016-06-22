// gcc -std=iso9899:1999 iso9899_1999.c -o iso9899_1999.linux
// gcc -std=iso9899:1999 -DNDEBUG iso9899_1999.c -o iso9899_1999.linux.release

#include <stdio.h>
#include <iso646.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include <stdarg.h>
#include <time.h>


void argFunci(int argNum, ...)
{
  va_list ap;
  va_start(ap, argNum);
  for(int i=0; i<argNum; i++)
    {
      
      printf("(%d(i): %d)\n", (i+1), va_arg(ap, int));

    }

  va_end(ap);
}


int main(int argc, char* argv[])
{
  printf("__func__: %s\n", __func__);

  uint8_t ui8 = 20;
 
  if( ui8<30 and true)
    {
      printf("and useful.\n");
    }

  //assert(false);
  /* assert(true);   */

  uint8_t ui8var = 65;
  if(isalpha(ui8var))
    {
      printf("isalhpa(%d)\n", ui8var);
    }
  else
    {
      printf("else isalhpa(%d)\n", ui8var);
    }

  const char* ch8dec = "888";
  printf("%s:%d \n", ch8dec, atol(ch8dec));

  argFunci(2, 10, 20);

  printf("CLOCKS_PER_SEC: %d\n", CLOCKS_PER_SEC);

  char* prog_name = argv[0];
  size_t namelen = strlen(argv[0]);
  strncpy(prog_name, "hhah", namelen);
  memset(prog_name+4, 0, namelen-4);
  getchar();
  return EXIT_SUCCESS;
}
