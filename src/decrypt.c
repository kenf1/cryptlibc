#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

//backend logic (decrypt only)
char* decryptlogic(const char* inputstr,const char* refstr,int offset){
    int input_len = strlen(inputstr);
    int ref_len = strlen(refstr);
    char* result = (char*)malloc(input_len + 1);

    //unable to allocate memory
    if(!result){
        return NULL;
    }

    //loop over each char in inputstr
    for(int i = 0;i < input_len;i++){
        char c = inputstr[i];
        if(isalpha(c)){
            int base = isupper(c) ? 'A' : 'a';
            int ref_index = -1;

            //index of char in refstr
            for(int j = 0;j < ref_len;j++){
                if(tolower(refstr[j]) == tolower(c)){
                    ref_index = j;
                    break;
                }
            }

            //loop if overflow
            if(ref_index != -1){
                int shift = (c - base - offset + 26) % 26; //diff
                result[i] = (char)(shift + base);
            }else{
                result[i] = c;
            }
        }else{
            result[i] = c;
        }
    }

    //end of string
    result[input_len] = '\0';
    return result;
}

//confirm input matches expected
void confirmStr(char* input,char* expected){
    if (strcmp(input,expected) == 0){
        printf("Input string matches expected string\n");
    } else {
        printf("Input string does not match expected string\n");
    }
}

int main(){
    //params
    const char* input = "Ifmmp, Xpsme!";
    const char* reference = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890";
    int offset = 1;

    //decrypt
    const char* res = decryptlogic(input,reference,offset);

    //confirm successful decryption
    const char* expected = "Hello, World!";
    confirmStr(res,expected);

    return 0;
}