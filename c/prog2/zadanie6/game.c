// Includes
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>


// Ansi colors - source https://gist.github.com/RabaDabaDoba/145049536f815903c79944599c6f952a
// Regular text
#define BLK "\e[0;30m"
#define RED "\e[0;31m"
#define GRN "\e[0;32m"
#define YEL "\e[0;33m"
#define BLU "\e[0;34m"
#define MAG "\e[0;35m"
#define CYN "\e[0;36m"
#define WHT "\e[0;37m"

// Regular bold text
#define BBLK "\e[1;30m"
#define BRED "\e[1;31m"
#define BGRN "\e[1;32m"
#define BYEL "\e[1;33m"
#define BBLU "\e[1;34m"
#define BMAG "\e[1;35m"
#define BCYN "\e[1;36m"
#define BWHT "\e[1;37m"

// Special
#define ITALIC "\e[3m"
#define RESET "\e[0m"

// You can change those, if you want, but words are lenght of COLUMNS
#define ROWS 6
#define COLUMNS 5

// Word database
char* wordDB[] = {"sigma", "based", "truth", "below", "click", "phone", "china", "stuff", "magic", "bound", "noted", "voice", "field", "error", "grace", "anger", "claim", "skill", "crime", "fruit", "point", "woman", "yield", "night", "south", "logic", "class", "scale", "scope", "alarm", "grand", "billy", "links", "smart", "carry", "plain", "prime", "issue", "floor", "sport", "enter", "story", "drove", "great", "clock", "split", "study", "close", "given", "globe", "begin", "jimmy", "ready", "trial", "event", "metal", "judge", "pilot", "pound", "solid", "while", "block", "fifty", "price", "after", "local", "human", "bring", "chair", "upset", "limit", "tried", "those", "pride", "queen", "harry", "extra", "aware", "drill", "forty", "motor", "again", "novel", "water", "sense", "mouse", "blame", "gross", "heavy", "paint", "beach", "terry", "blind", "agent", "chain", "peace", "baker", "depth", "alert", "stone", "leave", "glass", "march", "solve", "today", "phase", "shirt", "would", "spent", "until", "newly", "video", "staff", "plant", "lower", "dress", "place", "focus", "worth", "jones", "noise", "worse", "acute", "dozen", "built", "route", "brief", "light", "found", "model", "month", "state", "press", "bench", "score", "booth", "needs", "wound", "apart", "empty", "dream", "fully", "plate", "prove", "shift", "minus", "among", "pitch", "power", "shoot", "stand", "drink", "elite", "panel", "sugar", "grade", "broke", "cover", "print", "avoid", "maria", "above", "frank", "input", "image", "truck", "speak", "prize", "fleet", "funny", "smith", "along", "strip", "adult", "offer", "watch", "union", "shell", "sight", "layer", "tight", "break", "force", "worst", "curve", "enjoy", "apple", "store", "texas", "stake", "party", "thing", "trust", "refer", "thick", "crowd", "mouth", "throw", "worry", "sized", "boost", "agree", "check", "wheel", "birth", "every", "group", "mayor", "brown", "think", "super", "roger", "spend", "cross", "maybe", "royal", "shall", "laser", "audit", "prior", "brand", "usage", "badly", "young", "never", "teach", "vital", "doing", "faith", "proud", "these", "usual", "henry", "sorry", "fresh", "guard", "drive", "brain", "women", "large", "ocean", "spare", "theme", "three", "steam", "order", "earth", "short", "legal", "fiber", "clear", "stood", "upper", "reach", "table", "audio", "laugh", "quite", "apply", "youth", "going", "cheap", "radio", "chose", "aside", "their", "forth", "stage", "rough", "clean", "front", "touch", "abuse", "meant", "other", "thank", "write", "quiet", "where", "grown", "array", "entry", "later", "storm", "debut", "ought", "allow", "rapid", "threw", "board", "cable", "ratio", "taken", "admit", "whole", "teeth", "delay", "often", "trade", "broad", "breed", "seven", "mixed", "north", "moral", "frame", "stock", "treat", "argue", "dated", "alive", "small", "alone", "final", "tries", "learn", "wrote", "space", "adopt", "flash", "loose", "least", "arise", "value", "plane", "fixed", "court", "inner", "label", "shape", "under", "count", "lunch", "ahead", "chest", "spoke", "total", "trend", "match", "sweet", "guest", "mount", "heart", "calif", "being", "forum", "grass", "fluid", "guess", "valid", "river", "child", "wrong", "known", "range", "tough", "horse", "stuck", "truly", "sixth", "exact", "coach", "craft", "alike", "could", "Angle", "cream", "slide", "arena", "house", "photo", "began", "quick", "whose", "daily", "paper", "taxes", "sleep", "catch", "train", "chart", "first", "actor", "dying", "chase", "theft", "tired", "suite", "fraud", "roman", "draft", "proof", "crash", "guide", "shock", "speed", "still", "buyer", "music", "build", "lucky", "smoke", "round", "coast", "happy", "sharp", "lewis", "there", "unity", "times", "black", "stick", "tower", "rural", "sound", "album", "basic", "scene", "steel", "waste", "ideal", "giant", "alter", "asset", "eager", "death", "peter", "early", "basis", "might", "civil", "lease", "chief", "maker", "index", "smile", "award", "undue", "dealt", "fight", "shown", "movie", "urban", "bases", "doubt", "style", "title", "begun", "hence", "rival", "share", "topic", "false", "angry", "which", "fault", "about", "raise", "nurse", "sixty", "fifth", "crown", "lying", "white", "hotel", "media", "visit", "money", "enemy", "drawn", "minor", "blood", "robin", "sheet", "drama", "joint", "occur", "twice", "piece", "green", "dance", "exist", "equal", "japan", "right", "lives", "bread", "taste", "world", "grant", "cause", "serve", "virus", "shelf", "since", "level", "track", "third", "start", "cycle", "eight", "major"};
// char* wordDB[] = {"penis", "sigma"};

// Wordle in fancy text with ansi colors
// source - https://www.coolgenerator.com/ascii-text-generator
char* wordle[128] = {"\e[4;32m██\e[0;33m╗    \e[4;32m██\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██████\e[0;33m╗ \e[4;32m██\e[0;33m╗     \e[4;32m███████\e[0;33m╗", "\e[4;32m██\e[0;33m║    \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m╔═══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m║     \e[4;32m██\e[0;33m╔════╝", "\e[4;32m██\e[0;33m║ \e[4;32m█\e[0;33m╗ \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║   \e[4;32m██\e[0;33m║\e[4;32m██████\e[0;33m╔╝\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║     \e[4;32m█████\e[0;33m╗  ", "\e[4;32m██\e[0;33m║\e[4;32m███\e[0;33m╗\e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║   \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m╔══\e[4;32m██\e[0;33m╗\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██\e[0;33m║     \e[4;32m██\e[0;33m╔══╝  ", "\e[0;33m╚\e[4;32m███\e[0;33m╔\e[4;32m███\e[0;33m╔╝╚\e[4;32m██████\e[0;33m╔╝\e[4;32m██\e[0;33m║  \e[4;32m██\e[0;33m║\e[4;32m██████\e[0;33m╔╝\e[4;32m███████\e[0;33m╗\e[4;32m███████\e[0;33m╗", "\e[0;33m ╚══╝╚══╝  ╚═════╝ ╚═╝  ╚═╝╚═════╝ ╚══════╝╚══════╝"};

// Hope this is gonna work
void clear_terminal() {
  const char *CLEAR_SCREEN_ANSI = "\e[1;1H\e[2J\0";
  write(STDOUT_FILENO, CLEAR_SCREEN_ANSI, 12);
}

// Whole string to lower, needs malloc  // ? optimize
char *strlwr(char *str) {
    unsigned char *p = (unsigned char *)str;

    while (*p) {
        *p = tolower((unsigned char)*p);
        p++;
    }

    return str;
}

// Check if letter is in soltion, if yes, return 1 so we can print it yellow
int letter_in_key(char letter, char *key) {
    for (int l=0; l<(int)strlen(key); l++) {
        if (tolower(letter) == tolower(key[l])) {
            return 1;
        }
    }
    return 0;
}

int generate_table(char** userInput, char* key, int round) {
    // Table ROWS x COLUMNS
    char letter, keyLetter;
    for (int row=0; row<=ROWS*2; row++) {
        if (row%2 == 1) {  // print letters
            if (row/2 == round) {
                printf(RED "%2d." RESET, row/2);
                printf(" |");
            } else {
                printf("%2d. |", row/2);
            }
           
            for (int column=0; column<COLUMNS*2; column++) {
                if (column%2 == 0) {
                    letter = toupper(userInput[row/2][column/2]);
                    keyLetter = toupper(key[column/2]);
                    if (letter == keyLetter) {  // Green letter
                        printf(GRN "%c" , letter);
                    } else if (letter_in_key(letter, key) == 1) {  // Yellow letter
                        printf(YEL "%c" , letter);
                    } else {
                        printf("%c", letter);  // White letter
                    }
                    
                } else {
                    printf(RESET "|");  // Reset color before next letter
                }
            }
        } else {  // print lines between words
            printf("    ");  // Filler
            for (int column=0; column<=COLUMNS*2; column++) {
                printf("%c", "+-"[column%2]);
            }
        }
        printf("\n");
    }

    // TODO optimize
    char* keyLower = (char*)malloc(COLUMNS);
    char* inputLower = (char*)malloc(COLUMNS);
    strcpy(keyLower, key);
    strcpy(inputLower, userInput[round]);
    keyLower = strlwr(keyLower);
    inputLower = strlwr(inputLower);

    if (strcmp(inputLower, keyLower) == 0) {
        free(keyLower);
        free(inputLower);
        return 1;
    }
    return 0;
}

// Clear buffer, prevent overflow
void clear_buffer(){
    int c;
    while ((c = getchar()) != '\n' && c != EOF){
        continue;
    }
}

// Function to print fancy 'wordle' text
void print_wordle() {
    printf("\n"); 

    // Printing each line
    for (int i = 0; i < 6; i++) {
        printf("%s\n", wordle[i]);
    }

    // Printing creator of this creation
    printf("%s%sby anonymous %sFEI STU%s%sdent%s\n", RESET, ITALIC, BWHT, RESET, ITALIC, RESET);
}

// Main
int main() {
    char* array[ROWS];

    srand(time(0));

    // Create empty string for dynaminc setting of columns
    char emptyString[COLUMNS];
    for (int c=0; c<COLUMNS; c++) {
        emptyString[c] = ' ';
    }

    // Fill array
    for (int r=0; r < ROWS; r++) {
        array[r] = emptyString;
    }

    // clear_terminal();
    // print_wordle();

    // printf("\nPress %sENTER%s to continue...\n", ITALIC, RESET);
    // getchar();
    // clear_terminal();

    // printf("Good job, let's play!\n");
    // generate_table();
    // getchar();

    
    clear_terminal();

    int SIZE_OF_DB = sizeof(wordDB)/sizeof(wordDB[0]);
    char* wordleSolution = wordDB[rand() % SIZE_OF_DB];
    // wordleSolution = "sigma";
    printf("Database has %d words\n", SIZE_OF_DB);

    generate_table(array, wordleSolution, 0);

    for (int round=0; round<ROWS; round++) {
        
        printf("\nGuess the Hidden Word\n-> ");
        array[round] = (char *)malloc(sizeof(char *));
        scanf("%5s", array[round]);
        for (int check=(int)strlen(array[round]); check<COLUMNS; check++) {
            array[round][check] = '-';
        }
        clear_buffer();
        clear_terminal();

        if (generate_table(array, wordleSolution, round) == 1) {
            printf(YEL "\nYou won, word was" GRN " %s\n" RESET, wordleSolution );
            break;
        } else if (round == ROWS -1) {
            printf(RED "\nYOU LOST GG WP ff15, word was %s\n" RESET, wordleSolution);
        }
    }

    return 0;
}
