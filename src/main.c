#include <stdio.h>
#include <stdlib.h>
#include "cryptlibc.h"

int main(){
    const char* input = "Hello, World!";
    const char* reference = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    int offset = 1;

    //encrypt
    char* result = cryptlogic(input,reference,offset);
    printf("Shifted: %s\n",result);

    //free allocated memory
    free(result);

    return 0;
}