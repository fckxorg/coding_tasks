#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poetry_funcs.h"
#include "tests.h"

int main ()
{
  testGettingFileSize ();
  testGettingNumberOfLines ();
  testUpperCase ();
  testComparingStrings ();
  testComparingStringsFromEnd ();


  printf ("Provide filepath to file you want to sort strings in: ");

  char filename[FILENAME_MAX] = {};
  scanf ("%s", filename);

  int file_size = getFileSize (filename);
  char *file_data = (char *) calloc (file_size + 1, sizeof (char));
  char *file_data_copy = (char *) calloc (file_size + 1, sizeof (char));

  readFile (filename, file_size, file_data);

  memcpy (file_data_copy, file_data, file_size * sizeof (char));

  int n_lines = getNumberOfLines (file_data);

  auto *index = (StringBoundaries *) calloc (n_lines, sizeof (StringBoundaries));

  getStringsBoundaries (file_data, file_size, index);
  sortStrings (index, n_lines);

  printf ("Provide filepath for storing sorted data: ");
  scanf ("%s", filename);

  writeFileFromIndex (filename, index, n_lines);

  sortStringsBackwards (index, n_lines);

  writeFileFromIndex (filename, index, n_lines);
  writeFileFromBuffer (filename, file_data_copy, file_size);

  free (file_data);
  free (file_data_copy);
  free (index);

  return 0;
}