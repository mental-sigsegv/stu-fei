#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <string.h>

int d, p, u, l, r, R;
char pole[1001];
char replace_string[30];

void numremove () {
    int j = 0;

    for (int i = 0; i < (int) strlen(pole); i++) {
        if (isdigit(pole[i])) {
            pole[i] = -6;
        }
    }
    
    for (int i = 0; i < (int) strlen(pole); i++) {
        if (pole[i] == -6) {
        }
        else {
            pole[j] = pole[i];
            j++;
        }    
    }
    pole[j] = '\0'; 
}

void punctremove () {
    int j = 0;

    for (int i = 0; i < (int) strlen(pole); i++) {
        if (ispunct(pole[i])) {
            pole[i] = -6;
        }
    }
    
    for (int i = 0; i < (int) strlen(pole); i++) {
        if (pole[i] == -6) {
        }
        else {
            pole[j] = pole[i];
            j++;
        }    
    }
    pole[j] = '\0'; 
}

void lowertouppercase () {
    for (int i = 0; i < (int) strlen(pole); i++) {
        pole[i] = toupper(pole[i]);
    }
}

void uppertolowercase () {
    for (int i = 0; i < (int) strlen(pole); i++) {
        pole[i] = tolower(pole[i]);
    }
}

void alphanumeric () {
    for (int i = 0; i < (int) strlen(pole); i++) {
        if (isalnum(pole[i])) {
            
        }
        
    }
}

int getopt(int argc, char *const argv[], const char *optstring);

int main(int argc, char *argv[]){

	int opt;
	char* optstring = ":dpulr:R:";

    while ((opt = getopt(argc, argv, optstring)) != -1) {
        switch (opt) {
            case 'd':
                d = 1;
                break;
            case 'p':
                p = 1;
                break;
            case 'u':
                u = 1;
            	break;
            case 'l':
                l = 1;
                break;
            case 'r':
                r = 1;
                strcpy(replace_string, optarg);
                printf("%s", replace_string);
                break;
            case 'R':
                R = 1; 
                break;
            default: /* '?' alebo ':' */
                if (optopt == 'r') || (optopt == 'R') {
                    return 2;
                }
                
                return 1;
        }
    }

    while(strcmp((fgets(pole, 1001, stdin)), "\n") != 0) {
    
        if (d == 0) {
            numremove();
        }

        if (p == 0) {
            punctremove();
        }

        if (u == 1) {
            lowertouppercase();
        }

        if (l == 1) {
            uppertolowercase();
        }
        
        
        printf("%s", pole);
    }

    if(optind < argc){
            for(int i=optind;i<argc;i++){
                printf("Non-option CMD argument: %s\n",argv[i]);
            }
        }

	return 0;
}