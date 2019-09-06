//
// Created by maxim on 06.09.19.
//
int writeFile (char *filepath, char **strings_starts, int n_lines);

int getFileSize (char *filepath);

int getNumberOfLines (char *file_data);

void getStringsStarts (char *file_data, int file_size, char **string_starts);

int compareStrings (const void *first_string, const void *second_string);

int readFile (char *filepath, int file_size, char *file_data);

void sortStrings (char **string_starts, int n_lines);