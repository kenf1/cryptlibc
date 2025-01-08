#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

/*
    backend logic (encrypt + decrypt)
    version = "encrypt" or "decrypt"
*/
char* cryptlogic(
    const char* version,
    const char* inputstr,
    const char* refstr,
    int offset
) {
    //version only "encrypt" or "decrypt" accepted as args
    if (strcmp(version, "encrypt") != 0 && strcmp(version, "decrypt") != 0) {
        printf("Invalid input detected for `version` argument. Accepted values are `encrypt` or `decrypt`.\nPlease try again.\n");
        return NULL;
    }

    //other args
    int input_len = strlen(inputstr);
    int ref_len = strlen(refstr);
    char* result = (char*)malloc(input_len + 1);

    //unable to allocate memory
    if (!result) {
        return NULL;
    }

    //loop over each char in inputstr
    for (int i = 0;i < input_len;i++) {
        char c = inputstr[i];
        if (isalpha(c)) {
            int base = isupper(c) ? 'A' : 'a';
            int ref_index = -1;

            //index of char in refstr
            for (int j = 0;j < ref_len;j++) {
                if (tolower(refstr[j]) == tolower(c)) {
                    ref_index = j;
                    break;
                }
            }

            //loop if overflow
            if (ref_index != -1) {
                int shift = (c - base + (strcmp(version, "encrypt") ? offset : -offset) + 26) % 26;

                result[i] = (char)(shift + base);
            }
            else {
                result[i] = c;
            }
        }
        else {
            result[i] = c;
        }
    }

    //end of string
    result[input_len] = '\0';
    return result;
}