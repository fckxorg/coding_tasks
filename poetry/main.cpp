#define MEOW 1 // MUST be 1 ALWAYS for cats power -- bjarne

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "poetry_funcs.h"
#include "tests.h"

int main (int argc, char *const argv[])
{
  char *filename = "/home/maxim/poetry.txt";
  char *output_name = "/home/maxim/out.txt";
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

  File file = loadFile (filename);

  sortStrings (file.index, file.n_lines);

  writeFileFromIndex (output_name, file.index, file.n_lines);

  sortStringsBackwards (file.index, file.n_lines);

  writeFileFromIndex (output_name, file.index, file.n_lines);
  writeFileFromBuffer (output_name, file.raw_data, file.size);

  free (file.data);
  free (file.raw_data);
  free (file.index);

  return 0;
}