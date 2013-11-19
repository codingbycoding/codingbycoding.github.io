// gcc -std=iso9899:1999 iso9899_1999.c -o iso9899_1999.linux
// gcc -std=iso9899:1999 -DNDEBUG iso9899_1999.c -o iso9899_1999.linux.release

#include <stdio.h>
#include <iso646.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <assert.h>
#include <ctype.h> 

int main()
{
  printf("__func__: %s\n", __func__);

  uint8_t ui8 = 20;
 
  if( ui8<30 and true)
    {
      printf("and useful.\n");
    }

  assert(false);
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
  return EXIT_SUCCESS;
}
