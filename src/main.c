#include <stdio.h>
#include <stdlib.h>
#include "cryptlibc.h"

int main(){
    const char* input = "Hello, World!";
    const char* reference = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    int offset = 1;

    //encrypt
    char* result = cryptlogic("1encrypt",input,reference,offset);
    printf("Shifted: %s\n",result);

    //decrypt
    char* result1 = cryptlogic("decrypt",result,reference,offset);
    printf("De-shifted: %s\n",result1);

    //free allocated memory
    free(result);
    free(result1);

    return 0;
}