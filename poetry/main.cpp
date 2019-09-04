#include <string.h>
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>

void writeFile (char *filepath, char **strings_starts, int n_lines)
{
  /*!Writes strings to file located in provided path
   * @param filepath path to file location
   * @param strings_start array of pointers to strings to write
   * @param n_lines number of lines in file
   * */
  assert(filepath);
  assert(strings_starts);

  FILE *file = fopen (filepath, "w");

  if (!file)
    {
      perror ("Failed to open file");
    }

  for (int i = 0; i < n_lines; i++)
    {
      fprintf (file, "%s\n", strings_starts[i]);
    }
  fclose (file);
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
    }

  int file_size = 0;
  fseek (file, 0, SEEK_END);
  file_size = ftell (file);
  fclose (file);

  return file_size;
}

int getNumberOfLines (char *file_data)
{
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
void readFile (char *filepath, int file_size, char *file_data)
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
    }

  fseek (file, 0, SEEK_SET);
  fread (file_data, sizeof (char), file_size, file);
  fclose (file);
}

void getStringsStarts (char *file_data, int file_size, char **string_starts)
{
  /*!Writes list of pointers to string starts
   * @param file_data array with file_data
   * @param file_size length of file in symbols
   * @param string_starts array for pointers storing
   * */
  assert (file_data);
  assert (string_starts);

  int line = 0;

  string_starts[line] = file_data;
  for (int i = 1; i < file_size; i++)
    {
      if (file_data[i - 1] == '\n')
        {
          file_data[i - 1] = '\0';
          line++;
          string_starts[line] = &file_data[i];
        }
    }
}

int compareStrings (const void *first_string, const void *second_string)
{
  assert(first_string);
  assert (second_string);

  char *arg1 = *((char **) first_string);
  char *arg2 = *((char **) second_string);

  while (arg1 == arg2 && *arg1)
    {
      arg1++;
      arg2++;
    }
  int result = *arg1 - *arg2;
  if (result > 0)
    {
      return 1;
    }
  if (result < 0)
    {
      return -1;
    }

  return 0;
}

void sortStrings (char **string_starts, int n_lines)
{
  /*!Sorts strings by pointers in array
   * @param string_starts array of pointers to string starts
   * @param n_lines number of lines in file
   * */
  assert (string_starts);

  qsort (string_starts, n_lines, sizeof (char *), compareStrings);
}

int main ()
{
  printf ("Provide filepath to file you want to sort strings in: ");

  int MAX_FILENAME_LENGTH = 500;
  char filename[MAX_FILENAME_LENGTH];
  scanf ("%s", filename);

  int file_size = getFileSize (filename);

  char *file_data = (char *) calloc (file_size + 1, sizeof (char));
  readFile (filename, file_size, file_data);

  int n_lines = getNumberOfLines (file_data);

  char **string_starts = (char **) calloc (n_lines, sizeof (char *));
  getStringsStarts (file_data, file_size, string_starts);
  sortStrings (string_starts, n_lines);
  printf ("Provide filepath for storing sorted data: ");
  scanf ("%s", filename);
  writeFile (filename, string_starts, n_lines);

  return 0;
}