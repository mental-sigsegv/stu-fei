#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>


void store_pointers(char* from_arr, char** to_arr) {
    char letter;
    int p_adress=0;

    for (int i = 0; i < (int)strlen(from_arr); i++) {
        
        letter = from_arr[i];
        if ((letter != ' ') && (isalnum(letter))) {
            if (i == 0) {
                    to_arr[p_adress] = &from_arr[i];
                    p_adress++;
            } else if (!(isalnum((unsigned int)from_arr[i-1]))) {
                to_arr[p_adress] = &from_arr[i];
                p_adress++;
            }
            to_arr[p_adress] = NULL;
        }
    }
}

int main() {
    char arr[1001] = "uik weqwe qaWWPr sidfbuisbyb32 23423u4ubg\n\0";  // array we wanna get pointers from
    char* p_arr[(int)strlen(arr) + 1];  // store array pointers
    char* ptr;
    char* replace_string = "HEJHOU";

    store_pointers(arr, p_arr);  // store pointers

    // pointers of the array
    for (int i = 0; i < (int)sizeof(p_arr)/8; i++) {
        if (p_arr[i] == NULL) {
            break;
        }
        ptr = p_arr[i];
        for (int j = 0; j < (int)strlen(replace_string); j++) {
            if ((*ptr == '\n') || (*ptr == ' ')) {
                break;
            }
            *ptr = replace_string[j];
            ptr++;
        }
        
    }

    for (int i = 0; i < (int)strlen(arr); i++) {
        printf("%c", arr[i]);
    }

    return 0;
}
