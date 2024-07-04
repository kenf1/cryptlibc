#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//max num chars allowed
#define MAX_LENGTH 50
#define REF_STRING "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890"

void promptUser(char *inputStr,int max_length);
char* cryptlogic(const char *action,const char *inputStr,const char *refStr,int offset);

int main(){
    //get string to encrypt
    char input[MAX_LENGTH];
    promptUser(input,MAX_LENGTH);

    //encrypt
    char *encryptStr = cryptlogic("encrypt",input,REF_STRING,1);
    printf("Encrypted output: %s\n",encryptStr);

    //free up memory (only if cryptlogic does not return "Error")
    if(strcmp(encryptStr,"Error") != 0){
        free(encryptStr);
    }

    return 0;
}

//prompt user for string to encrypt
void promptUser(char *inputStr,int max_length){
    //readline
    printf("Enter text to encrypt: ");
    fgets(inputStr,max_length,stdin);

    //rm \n if present
    inputStr[strcspn(inputStr,"\n")] = '\0';
}

//backend logic
char* cryptlogic(const char *action,const char *inputStr,const char *refStr,int offset){
    int i;
    int ref_len = strlen(refStr);
    int input_len = strlen(inputStr);

    /*
        allocate memory on heap for new string
            +1 for `\n` char, sizeof to return in bytes
    */
    char *result = (char*)malloc((input_len + 1) * sizeof(char));
    if(result == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    //loop over each char in string
    for(i = 0;inputStr[i] != '\0';i++){
        char upper_char = toupper(inputStr[i]);
        int index = strchr(refStr,upper_char) - refStr;

        /*
            used strcmp (C) instead of action == "encrypt" (C++)
                incorrect comparison compares memory address, not content
        */
        if(strcmp(action,"encrypt") == 0){
            //loop if overflow
            int new_index = (index + offset) % ref_len;

            //preserve upper & lower case
            if(isupper(inputStr[i])){
                result[i] = refStr[new_index];
            }else{
                result[i] = tolower(refStr[new_index]);
            }
        }

        if(strcmp(action,"decrypt") == 0){
            //loop if overflow
            int new_index = (index - offset) % ref_len;

            //preserve upper & lower case
            if(isupper(inputStr[i])){
                result[i] = refStr[new_index];
            }else{
                result[i] = tolower(refStr[new_index]);
            }
        }

        //catch all other edge cases
        if(strcmp(action,"encrypt") != 0 && strcmp(action,"decrypt") != 0){
            printf("Options are encrypt or decrypt\n");
            return "Error";
        }
    }

    //add null terminator (end of string)
    result[i] = '\0';

    return result;
}