#include <stdio.h>
#include <stdlib.h>
#include "cryptlibc.h"

int main(void) {
    CryptConfig cfg = {
        .version = "encrypt",
        .inputstr = "Hello, World!",
        .refstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
        .offset = 1
    };

    //encrypt
    char* encrypted = cryptlogic(&cfg);
    if (!encrypted) {
        return EXIT_FAILURE;
    }
    printf("Encrypted: %s\n", encrypted);

    // reuse same config but switch mode (decrypt)
    cfg.version = "decrypt";
    cfg.inputstr = encrypted;

    char* decrypted = cryptlogic(&cfg);
    if (!decrypted) {
        free(encrypted);
        return EXIT_FAILURE;
    }
    printf("Decrypted: %s\n", decrypted);

    free(encrypted);
    free(decrypted);

    return EXIT_SUCCESS;
}
