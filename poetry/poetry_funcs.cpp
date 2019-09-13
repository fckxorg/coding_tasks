//
// Created by maxim on 06.09.19.
//

#include "poetry_funcs.h"
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>


int writeFileFromBuffer (char *filepath, char *buffer, int file_size)
{
  /*!Writes string to file located in provided path
   * @param filepath path to file location
   * @param buffer buffer to write
   * @param file_size length of file
   * */

  assert(filepath);
  assert(buffer);

  FILE *file = fopen (filepath, "a");

  if (!file)
    {
      perror ("Failed to open file");
      return 1;
    }
  fwrite (buffer, sizeof (char), file_size, file);
}

int writeFileFromIndex (char *filepath, StringBoundaries *index, int n_lines)
{
  /*!Writes strings to file located in provided path
   * @param filepath path to file location
   * @param strings_start array of pointers to strings to write
   * @param n_lines number of lines in file
   * */
  assert(filepath);
  assert(index);

  FILE *file = fopen (filepath, "a");

  if (!file)
    {
      perror ("Failed to open file");
      return 1;
    }

  for (int i = 0; i < n_lines; i++)
    {
      fprintf (file, "%s\n", index[i].start);
    }
  fprintf (file, "\n");
  fclose (file);
  return 0;
}

// Completed
int getFileSize (char *filepath)
{
  /*!Returns file length in symbols, writes number of lines
   * @param filepath path to file location
   * @param n_lines pointer to
   * @return file_size length of file in symbols
   * */
  assert(filepath);

  FILE *file = fopen (filepath, "r");

  if (!file)
    {
      perror ("Failed to open file");
      return -1;
    }

  int file_size = 0;
  fseek (file, 0, SEEK_END);
  file_size = ftell (file);
  fclose (file);

  return file_size;
}

int getNumberOfLines (char *file_data)
{
  /*! Use this function to get number of lines in buffer
   * @param file_data pointer to buffer
   * @return n_lines number of lines in buffer
   * */

  assert(file_data);

  int n_lines = 0;

  while (*file_data)
    {
      if (*file_data == '\n')
        {
          n_lines++;
        }
      file_data++;
    }

  return n_lines;
}

// Completed
int readFile (char *filepath, int file_size, char *file_data)
{
  /*!Writes file data to array
   * @param filepath path to file location
   * @param file_size length of file in symbols
   * @param file_data array for file data storing
   * */
  assert(filepath);
  assert (file_data);

  FILE *file = fopen (filepath, "r");

  if (!file)
    {
      perror ("Failed to open file");
      return 1;
    }

  fseek (file, 0, SEEK_SET);
  fread (file_data, sizeof (char), file_size, file);
  fclose (file);
  return 0;
}

void getStringsBoundaries (char *file_data, int file_size, StringBoundaries *index)
{
  /*!Writes list of pointers to string starts
   * @param file_data array with file_data
   * @param file_size length of file in symbols
   * @param string_starts array for pointers storing
   * */
  assert (file_data);
  assert (index);

  int line = 0;

  index[line].start = file_data;
  for (int i = 1; i < file_size; i++)
    {
      if (file_data[i - 1] == '\n')
        {
          file_data[i - 1] = '\0';
          index[line].end = &file_data[i - 2];
          line++;
          index[line].start = &file_data[i];
        }
    }
  file_data[file_size - 1] = '\0';
  index[line].end = &file_data[file_size - 2];
}

char upperCase (char letter)
{
  /*! Use this function to get uppercase letter. If letter already uppercase returns current letter
   * @param letter letter to uppercase
   * @return letter uppercase version of letter
   * */

  if (letter > 'Z' && letter <= 'z')
    {
      letter -= 'a' - 'A';
      return letter;
    }
  if (letter >= 'A' && letter <= 'Z')
    {
      return letter;
    }
  return 0;
}

char *getPreviousLetter (char *symbol)
{
  /*! Use this function to get previous letter in buffer.
  * @param symbol ptr to current symbol in buffer
  * @return symbol ptr to previous letter in buffer
  * */


  assert (symbol);

  symbol--;

  while ((*symbol > 'z' || *symbol < 'A') && *symbol)
    {
      symbol--;
    }
  return symbol;
}

char *getNextLetter (char *symbol)
{
  /*! Use this function to get next letter in buffer.
   * @param symbol ptr to current symbol in buffer
   * @return symbol ptr to next letter in buffer
   * */

  assert (symbol);

  symbol++;

  while ((*symbol > 'z' || *symbol < 'A') && *symbol)
    {
      symbol++;
    }
  return symbol;
}

int compareStrings (const void *first_string, const void *second_string)
{
  /*! Use this method to compare two strings
   * @param first_string pointer to first buffer with string
   * @param second_string pointer to second buffer with string
   * @return negative value, zero or positive value, when first buffer is lower, equal or greater than second_buffer respective
   * */
  assert(first_string);
  assert (second_string);

  char *arg1 = (*((StringBoundaries *) first_string)).start;
  char *arg2 = (*((StringBoundaries *) second_string)).start;

  assert (arg1);
  assert (arg2);

  if (*arg1 < 'A' || *arg1 > 'z')
    {
      arg1 = getNextLetter (arg1);
    }
  if (*arg2 < 'A' || *arg2 > 'z')
    {
      arg2 = getNextLetter (arg2);
    }

  while (*arg1 == *arg2 && *arg1)
    {
      arg1 = getNextLetter (arg1);
      arg2 = getNextLetter (arg2);
    }

  int result = *arg1 - *arg2;

  if (result > 0)
    {
      return 1;
    }
  else if (result < 0)
    {
      return -1;
    }

  return 0;
}

int compareStringsBackwards (const void *first_string, const void *second_string)
{
  /*! Use this method to compare two strings from end to start
  * @param first_string pointer to first buffer with string
  * @param second_string pointer to second buffer with string
  * @return negative value, zero or positive value, when first buffer is lower, equal or greater than second_buffer respective
  * */

  assert(first_string);
  assert (second_string);

  char *arg1 = (*((StringBoundaries *) first_string)).end;
  char *arg2 = (*((StringBoundaries *) second_string)).end;

  assert (arg1);
  assert (arg2);

  if (*arg1 < 'A' || *arg1 > 'z')
    {
      arg1 = getPreviousLetter (arg1);
    }

  if (*arg2 < 'A' || *arg2 > 'z')
    {
      arg2 = getPreviousLetter (arg2);
    }

  while (*arg1 == *arg2 && *arg1)
    {
      arg1 = getPreviousLetter (arg1);
      arg2 = getPreviousLetter (arg2);
    }

  int result = upperCase (*arg1) - upperCase (*arg2);

  if (result > 0)
    {
      return 1;
    }
  else if (result < 0)
    {
      return -1;
    }

  return 0;
}

void sortStrings (StringBoundaries *index, int n_lines)
{
  /*!Sorts strings by pointers in array of structs
   * @param index array of structs with pointers to string starts
   * @param n_lines number of lines in file
   * */
  assert (index);

  qsort (index, n_lines, sizeof (StringBoundaries), compareStrings);
}

void sortStringsBackwards (StringBoundaries *index, int n_lines)
{
  /*!Sorts strings from end to start by pointers in array of structs
   * @param index array of structs with pointers to string starts
   * @param n_lines number of lines in file
   * */

  assert (index);

  qsort (index, n_lines, sizeof (StringBoundaries), compareStringsBackwards);
}
