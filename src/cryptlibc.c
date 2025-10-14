#include "cryptlibc.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static int is_valid_version(const char *version) {
  return (strcmp(version, "encrypt") == 0 || strcmp(version, "decrypt") == 0);
}

char *cryptlogic(const CryptConfig *config) {
  if (!config || !config->version || !config->inputstr || !config->refstr) {
    fprintf(stderr, "Invalid null argument in CryptConfig.\n");
    return NULL;
  }

  if (!is_valid_version(config->version)) {
    fprintf(stderr, "Invalid version: %s. Must be 'encrypt' or 'decrypt'.\n",
            config->version);
    return NULL;
  }

  int input_len = strlen(config->inputstr);
  int ref_len = strlen(config->refstr);

  if (ref_len == 0) {
    fprintf(stderr, "Reference string cannot be empty.\n");
    return NULL;
  }

  char *result = malloc(input_len + 1);
  if (!result) {
    perror("Memory allocation failed");
    return NULL;
  }

  int direction = (strcmp(config->version, "encrypt") == 0) ? config->offset
                                                            : -config->offset;

  for (int i = 0; i < input_len; i++) {
    char c = config->inputstr[i];

    if (isalpha(c)) {
      int base = isupper(c) ? 'A' : 'a';
      int shift = (c - base + direction + 26) % 26;
      result[i] = (char)(shift + base);
    } else {
      result[i] = c;
    }
  }

  result[input_len] = '\0';
  return result;
}
