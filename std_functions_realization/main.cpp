#include <stdio.h>
#include <assert.h>
// TODO add tests
void swap (char *first_character, char *second_character)
{
  char tmp = 0;

  tmp = *first_character;
  *first_character = *second_character;
  *second_character = tmp;
}

void reverse (char *buffer)
{
  char *curr = buffer;

  while (*curr)
    {
      curr++;
    }

  for (int j = 0; j < (curr - buffer) / 2; j++)
    {
      swap (buffer + sizeof (char) * j, curr - sizeof (char) * (j + 1));
    }

}

int custom_puts (const char *str)
{
  assert (str);

  const char *curr = str;

  while (*curr)
    {
      if (fputc (*curr, stdout) == EOF)
        {
          return EOF;
        }
      curr++;
    }

  return (size_t) (curr - str + 1);
}

char *custom_fgets (char *str, size_t amount, FILE *stream)
{
  assert (str);
  assert (stream);
  if (!amount)
    {
      return NULL;
    }

  char *curr = str;
  char cursor = 0;

  cursor = getc (stream);
  while (cursor && curr - str < amount)
    {
      *curr = cursor;
      cursor = getc (stream);
      curr++;
    }

  if (curr - str == 0)
    {
      return NULL;
    }
  return str;

}

char *custom_itoa (int number, char *buffer, int base = 10)
{
  /*! Interprets number to string. You must provide string buffer with enough space in it.
   * @param number number to interpretate
   * @param buffer string buffer for output
   * @param base base specifier, default is 10
   * @return buffer pointer to buffer start
   * */
  assert (buffer);
  assert (number);
  if (2 > base || base > 36)
    {
      return NULL;
    }

  char *curr = buffer;

  while (number != 0)
    {
      if (number % base < 10)
        {
          *curr = '0' + number % base;
        }
      else
        {
          *curr = 'A' + number % base - 10;
        }
      curr++;
      number /= base;
    }
  reverse (buffer);

  return buffer;
}

int custom_atoi (const char *str)
{
  /*! Interprets an integer value in a byte string pointed to by str
   * @param str pointer to a byte string
   * @return Integer value corresponding to the contents of str on success. If no conversion can be performed returns 0. If the converted value is out of range of integer type, the return value is undefined
   * */
  assert (str);

  int number = 0;
  int digit = 0;

  while (*str)
    {
      digit = (int) *str - '0';
      if (digit < 10 && digit > -1)
        {
          number *= 10;
          number += digit;
        }
      else
        {
          return number;
        }
      str++;
    }

  return number;
}

int main ()
{
  char str[] = "Linus Torvalds";
  int status_code = custom_puts (str);
  const int ITOA_TEST_VALUE = 42;
  char buffer[10] = {};
  char second_buffer[10] = {};

  printf ("Status code: %d\n", status_code);
  printf ("atoi output: %d\n", custom_atoi ("junk123"));
  printf ("itoa output: %s\n", custom_itoa (ITOA_TEST_VALUE, buffer, 3));

  return 0;
}