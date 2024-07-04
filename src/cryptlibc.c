#include <stdio.h>
#include <string.h>

//max num chars allowed
#define MAX_LENGTH 50

//prompt user for string to encrypt
void promptUser(char *inputStr,int max_length){
    printf("Enter text to encrypt: ");
    fgets(inputStr,max_length,stdin);

    //rm \n (if present)
    inputStr[strcspn(inputStr,"\n")] = '\0';
}

int main(){
    //get string to encrypt
    char input[MAX_LENGTH];
    promptUser(input,MAX_LENGTH);

    printf("%s\n",input);

    return 0;
}