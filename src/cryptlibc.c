#include <string.h>
#include <ctype.h>
#include <stdlib.h>

//backend logic (encrypt only)
char* cryptlogic(const char* inputstr,const char* refstr,int offset){
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
                int shift = (offset + ref_index) % 26;
                result[i] = (char)((c - base + shift + 26) % 26 + base);
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