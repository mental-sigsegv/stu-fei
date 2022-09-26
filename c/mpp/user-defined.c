#include <stdio.h>
#include <string.h>

struct Books {
   char  title[50];
   char  author[50];
   char  subject[100];
   int   book_id;
};  

int main()
{
    struct Books Book;

    strcpy(Book.title, "The Last Wish");
    strcpy(Book.author, "Andrzej Sapkowski");
    strcpy(Book.subject, "fantasy");
    Book.book_id = 120112;

    return 0;
}
