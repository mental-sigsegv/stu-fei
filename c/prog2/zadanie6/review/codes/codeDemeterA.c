#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
// #include <conio.h>
#include <time.h>
#include <windows.h>   
//symboly tabuľky
const unsigned char plus = 43;
const unsigned char straight1 = 179;
const unsigned char straight2 = 196;
const char letter[26]={'Q','W','E','R','T','Y','U','I','O','P','A','S','D','F','G','H','J','K','L','Z','X','C','V','B','N','M'};//písmená klávesnice
const char words[5][5] = {"WATER", "LINUX", "TABLE", "CHAIR", "MOUSE"};//skryté slovo
char word[5];

void SetColor(int text, int bg){ //vybrať farbu
    HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hStdOut, (WORD)((bg << 4) | text));
}

void reset() {//biela farba na písmená
    SetColor(7, 0);

}

void red() {
    SetColor(12, 0);
}
void yellow(){
  SetColor(6, 0);
}
void green() {
    SetColor(10, 0);
}


void setcursor(int x, int y){//vybrať miesto, kde bude kurzor
  HANDLE  hConsole; // ziskanie handle konzoly
  hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
  COORD point = {x,y};
  SetConsoleCursorPosition(hConsole, point); 
}

int line_horizontal(int x,int y){//nakresliť prvý riadok tabuľky
  setcursor(x,y);
  putchar(plus);
  for (int a=0; a<15; a++){
      setcursor(x=x+2,y);
      putchar(straight2);
    }
  setcursor(x,y);
  putchar(plus);
}

int line_vertical(int x,int y){//nakresliť druhý riadok tabuľky
  for (int b = 0; b < 6; b++){
    setcursor(x,y);
    putchar(straight1);
    x=x+6;
  }
}

int table(){//nakresliť celú tabuľku
  int y=5;
  for (int k =0; k<6; k++){
    line_horizontal(5,y);
    line_vertical(5,y+1);
    y= y+2;
  }
  line_horizontal(5,y);
}

char keyboard(){//umiestnenie písmen z klávesnice v konzole
  int n=0;
  int x=10;
  int k =11;
  int m=12;
  while (n<26){//písmená od Q po P
    if (n<10){
      setcursor(x,20);
      printf ("%c",letter[n]);
      x=x+2;
      n++;
    }
    if (9<n && n<19){//písmená od A po L
      setcursor(k,22);
      printf ("%c",letter[n]);
      k=k+2;
      n++;
    }
    if (18<n && n<26){//písmená od Z po M
      setcursor(m,24);
      printf ("%c",letter[n]);
      m=m+2;
      n++;
    }
    
  }

}


int keycol(char l){//farba písmen na klávesnici
  int n=0;
  int x=10;
  int k =11;
  int m=12;
  for(n=0; n<26; n++){
      if (n<10){//pre písmená od Q po P
        setcursor(x,20);
        if(toupper(l) == letter[n])
          printf ("%c",letter[n]);
        x=x+2;

      }
      if (9<n && n<19){//pre písmená od A po L
        setcursor(k,22);
        if(toupper(l) == letter[n])
          printf ("%c",letter[n]);
        k=k+2;

      }
      if (18<n && n<26){//pre písmená od Z po M
        setcursor(m,24);
        if(toupper(l) == letter[n])
          printf ("%c",letter[n]);
        m=m+2;
       
      }
    
  }
  
}

int isLetter(char letter, int n){//porovnať písmená cieľového slova so slovom zadaným používateľom
  for(int i=0; i<5; i++){
    if(word[i]==toupper(letter) && i==n){
      green();//farba písmen v závislosti od toho, či ste uhádli, alebo nie
      return 1;
    }
    else if(word[i]==toupper(letter)){
      yellow();//farba písmen v závislosti od toho, či ste uhádli, alebo nie
      return 0;
    }
  }
  red();
  return 0;
}

int word_one(int n){//používateľ zadáva slová z klávesnice
  char str1[6];
  printf ("\n");
  gets(str1);
  int x = 8;
  int con = 0;
  for(int i=0; i<5; i++){
    con += isLetter(str1[i], i);//porovnať písmená zadaného slova s cieľovým slovom.
    keycol(str1[i]);//farba
    setcursor(x,4+n*2);
    printf ("%c",str1[i]);
    reset();
    x=x+6;
  }
  if(con == 5){
    return 1;
  }
  return 0;
}


int main(int argc, char* argv[]){
system("cls");
srand(time(NULL));
strcpy(word, words[rand()%5]);
reset();
table();
keyboard();
int n, con;
for(n=1; n<=6; n++){
  setcursor(0, 28+n);
  con = word_one(n);
  setcursor(0, 28+n+4);
  if(con==1){
    printf("YOU WIN!!!");
    return 1;
  }
  
}
printf("YOU LOSE!!!");
setcursor(0, 28+n+4);
//Prosím, 10 bodov, nestačí na kvalifikáciu na skúšku, ďakujem!
}



