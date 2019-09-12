#include <stdio.h>
#include <stdlib.h>
#include "poetry_funcs.h"

int main ()
{
  printf ("Provide filepath to file you want to sort strings in: ");

  const int MAX_FILENAME_LENGTH = 500;
  char filename[MAX_FILENAME_LENGTH] = {};
  scanf ("%s", filename);

  int file_size = getFileSize (filename);

  char *file_data = (char *) calloc (file_size + 1, sizeof (char));
  readFile (filename, file_size, file_data);

  int n_lines = getNumberOfLines (file_data);

  auto *index = (StringBoundaries *) calloc (n_lines, sizeof (StringBoundaries));
  getStringsBoundaries (file_data, file_size, index);
  sortStrings (index, n_lines);

  printf ("Provide filepath for storing sorted data: ");
  scanf ("%s", filename);

  writeFile (filename, index, n_lines);

  sortStringsBackwards (index, n_lines);

  writeFile (filename, index, n_lines);

  free (file_data);
  free (index);

  return 0;
}