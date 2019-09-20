#define MEOW 1 // MUST be 1 ALWAYS for cats power -- bjarne

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poetry_funcs.h"
#include "tests.h"

int main (int argc, char *const argv[])
{
  char *filename;
  char *output_name;
  if (argc == 2 && strcmp (argv[1], "--test") == 0)
    {
      testGettingFileSize ();
      testGettingNumberOfLines ();
      testUpperCase ();
      testComparingStrings ();
      testComparingStringsFromEnd ();
    }
  if (argc == 5)
    {
      if (strcmp (argv[1], "-i") == 0)
        {
          filename = argv[2];
        }
      if (strcmp (argv[3], "-o") == 0)
        {
          output_name = argv[4];
        }
    }

#if MEOW

  int file_size = getFileSize (filename);
  char *file_data = (char *) calloc (file_size + 1, sizeof (char));
  char *file_data_copy = (char *) calloc (file_size + 1, sizeof (char));

  readFile (filename, file_size, file_data);

  memcpy (file_data_copy, file_data, file_size * sizeof (char));

  int n_lines = getNumberOfLines (file_data);

  auto *index = (StringBoundaries *) calloc (n_lines, sizeof (StringBoundaries));

  getStringsBoundaries (file_data, file_size, index);

#endif

  sortStrings (index, n_lines);

  writeFileFromIndex (output_name, index, n_lines);

  sortStringsBackwards (index, n_lines);

  writeFileFromIndex (output_name, index, n_lines);
  writeFileFromBuffer (output_name, file_data_copy, file_size);

  free (file_data);
  free (file_data_copy);
  free (index);

  return 0;
}