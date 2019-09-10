//
// Created by maxim on 06.09.19.
//
#include <assert.h>
#include <stdio.h>

#include "custom_funcs.h"
#include "service_funcs.h"

int custom_puts (const char *str, FILE *filestream)
{
  /*!Writes every character from the null-terminated string str to the output stream stream, as if by repeatedly executing fputc.
   * @param str pointer to string you want to write
   * @param filestream pointer to file instance
   * @return amount amount of written symbols
   * */
  assert (str);
  assert (filestream);

  const char *curr = str;

  while (*curr)
    {
      if (fputc (*curr, filestream) == EOF)
        {
          return EOF;
        }
      curr++;
    }

  return (size_t) (curr - str + 1);
}

char *custom_fgets (char *str, size_t amount, FILE *stream)
{
  /*!Reads at most count - 1 characters from the given file stream and stores them in the character array pointed to by str.
   * Parsing stops if end-of-file occurs or a newline character is found, in which case str will contain that newline character.
   * If no errors occur, writes a null character at the position immediately after the last character written to str.
   * @param str pointer to a char array for storing strings
   * @param amount maximum number of characters to write
   * @param stream pointer to file instance
   * @return str pointer to string with data
   * */
  assert (str);
  assert (stream);

  if (!amount)
    {
      return NULL;
    }

  char *curr = str;
  char cursor = 0;

  cursor = getc (stream);
  while (cursor != '\n' && curr - str < amount)
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

char *custom_itoa (int number, char *buffer, int base)
{
  /*! Interprets number to string. You must provide string buffer with enough space in it.
   * @param number number to interpretate
   * @param buffer string buffer for output
   * @param base base specifier, default is 10
   * @return buffer pointer to buffer start
   * */
  assert (buffer);

  bool is_negative = false;

  if (number < 0)
    {
      is_negative = true;
      number = -number;
    }

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
  if (is_negative)
    {
      *curr = '-';
    }

  curr++;
  *curr = '\0';

  reverse (buffer); 

  return buffer;
}

int custom_atoi (const char *str)
{
  /*! Interprets an integer value in a byte string pointed to by str
   * @param str pointer to a byte string
   * @return Integer value corresponding to the contents of str on success.
   * If no conversion can be performed returns 0.
   * If the converted value is out of range of integer type, the return value is undefined
   * */
  assert (str);

  int number = 0;
  int digit = 0;
  bool is_negative = false;

  while (*str)
    {

      digit = (int) *str - '0';
      if (digit < 10 && digit > -1)
        {
          number *= 10;
          number += digit;
        }
      else if (digit == '-' - '0')
        {
          is_negative = true;
        }
      else
        {
          break;
        }
      str++;
    }
  if (is_negative)
    {
      number = -number;
    }
  return number;
}