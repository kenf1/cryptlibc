#ifndef CRYPTLIBC_H
#define CRYPTLIBC_H

typedef struct {
    const char* version;   //"encrypt" or "decrypt"
    const char* inputstr;  //input string to process
    const char* refstr;    //reference characters (alphabet, symbols, etc.)
    int offset;            //shift amount
} CryptConfig;

char* cryptlogic(const CryptConfig* config);

#endif
