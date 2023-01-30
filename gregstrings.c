#include <stdio.h>
#include <stdlib.h>
#include "gregstrings.h"

int greg_string_length(char * string) {
  if (string == NULL) {
    return 0;
  }

  int i = 0;

  while(string[i] != '\0') {
    i++;
  }

  return i;
}

char * greg_string_copy(char * source, char * destination) {
  int source_length = greg_string_length(source);

  for (int i = 0; i < source_length; i++) {
    destination[i] = source[i];
  }

  destination[source_length] = '\0';
  return destination;
}

int greg_string_compare(char *a, char *b) {
  if (a == NULL && b == NULL) {
    return 0;
  }

  if (a == NULL || b == NULL) {
    return 1;
  }

  int i = 0;

  while(a[i] != '\0' && b[i] != '\0' &&  a[i] == b[i]) {
    i++;
  }

  if (a[i] == b[i]) {
    return 0;
  }

  return 1;
}

