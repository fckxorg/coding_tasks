//
// Created by maxim on 13.09.19.
//

#include "tests.h"
#include "poetry_funcs.h"
#include <stdio.h>
#include <stdlib.h>

int testGettingFileSize ()
{
  int file_size = 524;
  int evaluated = 0;

  evaluated = getFileSize ("test.txt");

  if (evaluated == file_size)
    {
      printf ("fileSize test passed\n");
      return 0;
    }
  printf ("fileSize test failed! Expected %d, got %d\n", file_size, evaluated);
  return 1;
}

int testGettingNumberOfLines ()
{
  int n_lines = 13;
  int evaluated = 0;

  int file_size = getFileSize ("test.txt");
  char *file_data = (char *) calloc (file_size + 1, sizeof (char));
  readFile ("test.txt", file_size, file_data);

  evaluated = getNumberOfLines (file_data);

  if (evaluated == n_lines)
    {
      printf ("getNumberOfLines test passed\n");
      return 0;
    }
  printf ("getNumberOfLines test failed! Expected %d, got %d\n", n_lines, evaluated);
  return 1;
}

int testUpperCase ()
{
  char evaluated_low = 0, evaluated_high = 0;

  char high_letter = 'A', low_letter = 'a';

  evaluated_low = upperCase (low_letter);
  evaluated_high = upperCase (high_letter);

  if (evaluated_low == high_letter)
    {
      if (evaluated_high == high_letter)
        {
          printf ("upperCase test passed\n");
          return 0;
        }
      printf ("upperCase test failed! Expected 'A', got '%c'\n", evaluated_high);
      return 1;
    }
  printf ("upperCase test failed! Expected 'A', got '%c'\n", evaluated_low);
  return 1;
}

int testComparingStrings ()
{
  char string1[] = "Abcde";
  char string2[] = "Acdex";

  StringBoundaries str1_bounds{};
  StringBoundaries str2_bounds{};

  str1_bounds.start = string1;
  str2_bounds.start = string2;

  int evaluated = compareStrings ((const void *) (&str1_bounds), (const void *) (&str2_bounds));

  if (evaluated == -1)
    {
      printf ("compareStrings test passed\n");
      return 0;
    }
  printf ("compareStrings test failed! Expected '-1', got '%d'\n", evaluated);
  return 1;
}

int testComparingStringsFromEnd ()
{
  char string1[] = "Abcde";
  char string2[] = "Acdxe";

  StringBoundaries str1_bounds{};
  StringBoundaries str2_bounds{};

  str1_bounds.end = string1 + 4;
  str2_bounds.end = string2 + 4;

  int evaluated = compareStringsBackwards ((const void *) (&str1_bounds), (const void *) (&str2_bounds));

  if (evaluated == -1)
    {
      printf ("compareStringsFromEnd test passed\n");
      return 0;
    }
  printf ("compareStringsFromEnd test failed! Expected '-1', got '%d'\n", evaluated);
  return 1;
}
