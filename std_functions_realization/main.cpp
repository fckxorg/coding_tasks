#include <stdio.h>
#include "custom_funcs.h"

int main ()
{
  char str[] = "Linus Torvalds";
  int status_code = custom_puts (str, stdout);
  const int ITOA_TEST_VALUE = 42;
  char buffer[10] = {};

  printf ("Status code: %d\n", status_code);
  printf ("atoi output: %d\n", custom_atoi ("12ji3"));
  printf ("itoa output: %s\n", custom_itoa (ITOA_TEST_VALUE, buffer, 10));

  return 0;
}