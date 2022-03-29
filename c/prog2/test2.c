#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

static int DIGITS=0, PUNCT=0, UPPER_CASE=0, LOWER_CASE=0, CASE_SENS=0, CASE_INSENS=0;

void store_pointers(char* from_arr, char** to_arr) {
    char letter;
    int p_adress=0;
    to_arr[0] = NULL;

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

void find_prefix(char* stringReplace, char** prefixes, int numOfPrefixes, char** pointersOfWords) {
    printf("%s\n%p\n%d\n%p\n", stringReplace, prefixes, numOfPrefixes, pointersOfWords);
    return;
    int ptr=0, l=0;
    char znak;
    char* PENIS;
    while (pointersOfWords[ptr] != NULL) {
        for (int pref = 0; pref < numOfPrefixes; pref++) {
            l = (int)strlen(prefixes[pref]);
            PENIS = pointersOfWords[ptr];
            if (strncmp(prefixes[pref], PENIS, l) == 0) {
                for (int i=0; i < (int)strlen(stringReplace); i++) {
                    znak = *PENIS;
                    if (!(isalnum(znak))) {
                        break;
                    } else {
                        *PENIS = stringReplace[i];
                        PENIS = PENIS + 1;
                    }
                    
                }
            }
        }
        ptr++;
    }
}

int main(int argc, char **argv) {
    // Define settings
    char line[MAX_LENGTH+1] = "karta BImetal+BIt 964 BI111-4299854 DIELO strom   stromCEK/429friolk\n\0";
    
    int opt;
	char* optstring = ":dplur:R:";  // TODO staci dat na zaciatok optstringu "-" a getopt presunie vsetky non option argumenty na koniec a zaregistruje aj to -e
    char* argString;

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'd':
                DIGITS = 1;
                break;
            case 'p':
                PUNCT = 1;
                break;
            case 'l':
                LOWER_CASE = 1;
                break;
            case 'u':
                UPPER_CASE = 1;
                break;
            case 'r':
            	CASE_SENS = 1;  //! store optarg into string
                argString = optarg;
            	break;
            case 'R':
            	CASE_INSENS = 1;  //! store optarg into string / pointer
                argString = optarg;
                break;
            
            default: /* '?' alebo ':' */   
                if ((optopt == 'r') || (optopt == 'R')) {
                    // printf("req. arg");
                    return 2;
                }
                // printf("wrong switch");
                return 1;  // TODO test in liunux env
        }
    }

    // printf("optind %d\nargc %d\n",optind, argc);


    // *Store optional argv
    char* optionalArgs[argc-optind];
    int c = 0;
    for (int i = optind; i < argc; i++) {
        optionalArgs[c] = argv[i];
        c++;
    }
    // optionalArgs[c] = '\0';

    char* pointersOfWords[(int)strlen(line)];
    store_pointers(line, pointersOfWords);

    // int j = 0;
    // while (pointersOfWords[j] != NULL) {
    //     printf("%p\n", pointersOfWords[j]);
    //     j++;
    // }
    
    find_prefix("123LEKvar", optionalArgs, (int)sizeof(optionalArgs)/8, pointersOfWords);

    printf("%s", line);
    // Print optional argv
    // for (int i = 0; i < (int)sizeof(optionalArgs)/8; i++) {
    //     printf("\n%s", optionalArgs[i]);
    // }
    return 0;
}