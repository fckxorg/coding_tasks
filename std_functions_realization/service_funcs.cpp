//
// Created by maxim on 06.09.19.
//

#include "service_funcs.h"

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

void swap (char *first_character, char *second_character)
{
  char tmp = 0;

  tmp = *first_character;
  *first_character = *second_character;
  *second_character = tmp;
}
