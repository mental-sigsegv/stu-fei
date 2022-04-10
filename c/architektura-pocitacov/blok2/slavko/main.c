#include <stdio.h>

void raid () {
    FILE *fa;
    FILE *fb;
    FILE *fc;
    FILE *fd;
    int a=0, b=0, c=0, d=0;
    fa= fopen("C:\\Users\\Klacik\\Desktop\\github\\stu-fei\\c\\architektura-pocitacov\\blok2\\slavko\\file01.txt","r");
    fb= fopen("C:\\Users\\Klacik\\Desktop\\github\\stu-fei\\c\\architektura-pocitacov\\blok2\\slavko\\file03.txt","r");
    fc= fopen("C:\\Users\\Klacik\\Desktop\\github\\stu-fei\\c\\architektura-pocitacov\\blok2\\slavko\\file04.txt","rb");
    fd= fopen("C:\\Users\\Klacik\\Desktop\\github\\stu-fei\\c\\architektura-pocitacov\\blok2\\slavko\\output.txt","w");
    while(((a=fgetc(fa))!=EOF) && ((b=fgetc(fb))!=EOF) && ((c=fgetc(fc))!=EOF))
    {
        d = a ^ b ^ c;
        fprintf(fd, "%03d %c\n", d, d);
        // fputc(d,fd);
    }
    fclose(fa);
    fclose(fb);
    fclose(fc);
    fclose(fd);
}

int main()
{
    raid ();

    return 0;
}
