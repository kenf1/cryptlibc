#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "cryptlibc.h"

// helper to free + assert string equality
void assert_result(const char* actual, const char* expected, const char* test_name) {
    if (strcmp(actual, expected) == 0) {
        printf("[PASS] %s\n", test_name);
    }
    else {
        printf("[FAIL] %s: got '%s', expected '%s'\n", test_name, actual, expected);
        exit(EXIT_FAILURE);
    }
    free((void*)actual);
}

void test_encrypt_basic() {
    CryptConfig cfg = {
        .version = "encrypt",
        .inputstr = "Hello",
        .refstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
        .offset = 1
    };
    char* result = cryptlogic(&cfg);
    assert_result(result, "Ifmmp", "Encrypt Basic");
}

void test_decrypt_basic() {
    CryptConfig cfg = {
        .version = "decrypt",
        .inputstr = "Ifmmp",
        .refstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
        .offset = 1
    };
    char* result = cryptlogic(&cfg);
    assert_result(result, "Hello", "Decrypt Basic");
}

void test_nonalpha() {
    CryptConfig cfg = {
        .version = "encrypt",
        .inputstr = "Hello, World! 123",
        .refstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
        .offset = 1
    };
    char* result = cryptlogic(&cfg);
    assert_result(result, "Ifmmp, Xpsme! 123", "Encrypt Non-Alphabet");
}

void test_invalid_version() {
    CryptConfig cfg = {
        .version = "invalid",
        .inputstr = "Hello",
        .refstr = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890",
        .offset = 1
    };
    char* result = cryptlogic(&cfg);
    if (result == NULL) {
        printf("[PASS] Invalid Version Test\n");
    }
    else {
        printf("[FAIL] Invalid Version Test: expected NULL\n");
        free(result);
        exit(EXIT_FAILURE);
    }
}

void test_empty_refstr() {
    CryptConfig cfg = {
        .version = "encrypt",
        .inputstr = "Hello",
        .refstr = "",
        .offset = 1
    };
    char* result = cryptlogic(&cfg);
    if (result == NULL) {
        printf("[PASS] Empty Refstr Test\n");
    }
    else {
        printf("[FAIL] Empty Refstr Test: expected NULL\n");
        free(result);
        exit(EXIT_FAILURE);
    }
}

int main(void) {
    test_encrypt_basic();
    test_decrypt_basic();

    test_nonalpha();
    test_invalid_version();

    test_empty_refstr();

    printf("All tests finished.\n");
    return 0;
}
