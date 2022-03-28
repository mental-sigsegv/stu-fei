#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

#define MAX_LENGTH 1000

static int DIGITS=0, PUNCT=0, UPPER_CASE=0, LOWER_CASE=0, CASE_SENS=0, CASE_INSENS=0;

void update_line(char *arr) {
    char c;
    int i = 0, new_i = 0;
    while ((c = arr[i]) != '\n') {
        if (c != -1) {
            arr[new_i] = c;
            new_i++;
        }
        i++;
    }
    arr[new_i+1]='\n';
    arr[new_i+1]='\0';
}

void case_conversion(char *arr) {  
    if (UPPER_CASE == 1) {
        for (int i = 0; i < (int)strlen(arr); i++) {
            arr[i] = toupper(arr[i]);
        }
    } else if (LOWER_CASE == 1) {
        for (int i = 0; i < (int)strlen(arr); i++) {
            arr[i] = tolower(arr[i]);
        }
    } 
}

void edit_line(char *arr) {
    char letter;
    for (int i = 0; i < (int)strlen(arr); i++) {
        letter = arr[i];
        if ((letter == ' ') || isalpha(letter) || (letter == '\n')) {
            arr[i] = letter;
        } else {
            arr[i] = -1;
        }

        if ((DIGITS == 1) && (isalnum(letter))) {
            arr[i] = letter;
        }
        
        if ((PUNCT == 1) && (ispunct(letter))) {
            arr[i] = letter;
        } 

        if ((UPPER_CASE == 1) || (LOWER_CASE == 1)) {
            case_conversion(arr);
        }
    }
    return;
}


int main(int argc, char *argv[]) {
    // Define settings
    char line[MAX_LENGTH+1] = {'\0'};
    
    int opt;
	char* optstring = ":dplur:R:";  // TODO staci dat na zaciatok optstringu "-" a getopt presunie vsetky non option argumenty na koniec a zaregistruje aj to -e

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
                printf("%s", optarg);
            	break;
            case 'R':
            	CASE_INSENS = 1;  //! store optarg into string / pointer
                printf("%s", optarg);
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
    if(optind < argc){
    	for(int i=optind;i<argc;i++){
    		if (argv[i][0] == '-') {
                return 1;
            }
    	}
    }

    // Get line
    int safe_break = 0;  // !delete later
    while (1) {
        fgets(line, MAX_LENGTH, stdin);
        if (line[0] == '\n') {
            break;
        }
        edit_line(line);
        update_line(line);
        printf("%s", line);

        // !delete later
        if (safe_break > 20) {
            printf("FUCK YOU, YOU FUCKED UP");
            break;
        } else {
            safe_break++;
        }
        // !delete later

    }
    
    return 0;
}
