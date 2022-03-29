#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

static int DIGITS=0, PUNCT=0, UPPER_CASE=0, LOWER_CASE=0, CASE_SENS=0, CASE_INSENS=0;


int main(int argc, char **argv) {
    // Define settings
    char line[MAX_LENGTH+1] = {'\0'};
    
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


    printf("optind %d\nargc %d\n",optind, argc);


    // *Store optional argv
    char* optionalArgs[argc-optind];
    int c = 0;
    for (int i = optind; i < argc; i++) {
        optionalArgs[c] = argv[i];
        c++;
    }

    for (int i = 0; i < (int)sizeof(optionalArgs)/8; i++) {
        printf("%s\n", optionalArgs[i]);
    }
    return 0;
}