#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_LENGTH 50 //max num chars allowed
#define REF_STRING "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

void promptUser(char *inputStr,int max_length);
char* cryptlogic(const char *inputStr,const char *refStr,int offset);

int main(){
    //get string to encrypt
    char input[MAX_LENGTH];
    promptUser(input,MAX_LENGTH);

    //encrypt
    char *encryptStr = cryptlogic(input,REF_STRING,1);
    printf("Encrypted output: %s\n",encryptStr);

    //free up memory
    free(encryptStr);

    return 0;
}

//prompt user for string to encrypt
void promptUser(char *inputStr,int max_length){
    printf("Enter text to encrypt: ");
    fgets(inputStr,max_length,stdin);

    //rm \n (if present)
    inputStr[strcspn(inputStr,"\n")] = '\0';
}

//backend logic
char* cryptlogic(const char *inputStr,const char *refStr,int offset){
    int i;
    int ref_len = strlen(refStr);
    int input_len = strlen(inputStr);

    //allocate memory on heap for new string (+1 for `\n` char, sizeof to return in bytes)
    char *result = (char*)malloc((input_len + 1) * sizeof(char));
    if(result == NULL){
        printf("Memory allocation failed\n");
        exit(1);
    }

    //loop over each char in string
    for(i = 0;inputStr[i] != '\0';i++){
        if(isalpha(inputStr[i])){
            char upper_char = toupper(inputStr[i]);
            int index = strchr(refStr,upper_char) - refStr;
            int new_index = (index + offset) % ref_len;

            //preserve upper & lower case
            if(isupper(inputStr[i])){
                result[i] = refStr[new_index];
            }else{
                result[i] = tolower(refStr[new_index]);
            }
        }else{
            //char not in REF_STRING return as is
            result[i] = inputStr[i];
        }
    }

    result[i] = '\0';

    return result;
}