/*
Meno a priezvisko: Martin Klacik

POKYNY:
(1)  Implementujte funkcie tak, aby splnali popis pri ich deklaraciach.
(2)  Cela implementacia musi byt v tomto jednom subore.
(3)  Odovzdajte len tento zdrojovy subor (s vypracovanymi rieseniami).
(4)  Program musi byt kompilovatelny.
(5)  Globalne a staticke premenne su zakazane.
(6)  V ziadnom pripade nemente deklaracie funkcii, ktore mate za ulohu naprogramovat
     (nemente nazvy, navratove hodnoty, ani typ a pocet parametrov v zadanych funkciach).
     Nemente implementacie zadanych datovych typov, ani implementacie hotovych pomocnych funkcii
     (ak nie je v zadani ulohy uvedene inak).
(7)  V pripade potreby mozete kod doplnit o dalsie pomocne funkcie alebo datove typy.
(8)  Vase riesenie otestujte (vo funkcii 'main' a pomocou doplnenych pomocnych funkcii alebo datovych typov).
     Testovaci kod ale nebude hodnoteny.
(9)  Funkcia 'main' musi byt v zdrojovom kode posledna.
*/

#include <iostream>
#include <climits>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Pozicia v rovine
struct Position {
    int x; // x-ova suradnica
    int y; // y-ova suradnica
};

// Datum
struct Date {
    int year;  // rok
    int month; // mesiac
    int day;   // den
};

// Uspesnost vykonania funkcie
enum class Result {
    SUCCESS, // funkcia vykonana uspesne
    FAILURE  // chyba pri vykonavani funkcie
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia na standardny vystup vytlaci udaje v strukture.
    V implementacii musi byt pouzity 'std::cout'.

    Format tlace musi byt podla nasledujucich prikladov. Bez odriadkovania. Bez uvodzoviek. Dodrzte pouzitie medzier.
    Priklady:
        "x: 10, y: 20"
        "x: -12345, y: 2"

    PARAMETER:
        [in] position - pozicia, ktora bude vytlacena
*/
void print(const Position *position) {
    cout << "x: " << position->x << ", y: " << position->y;
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Implementujte rovnaku funkcionalitu ako v prvom priklade. Rozdiel je len typ parametra funkcie.
*/
void print(const Position &position) {
    cout << "x: " << position.x << ", y: " << position.y;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zo standardneho vstupu nacita postupne dve cisla. Ulozi ich ako x-ovu a y-ovu zlozku pozicie 'position'.
    V implementacii musi byt pouzity 'std::cin' a formatovany vstup.

    PARAMETER:
        - [out] position - pozicia, ktorej hodnoty sa nastavia podla udajov zo standardneho vstupu.

    VSTUPNE PODMIENKY:
        Text zadany na standardny vstup obsahuje dve cele cisla, ktore mozno reprezetovat typom 'int'.
        Nemusite osetrovat moznost chybnych udajov na standardnom vstupe.
 */
void readFromStandardInput(Position *position) {
    cin >> position->x;
    cin >> position->y;
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati najvacsiu hodnotu prvku pola 'data' a nastavi 'result' podla uspesnosti hladania.

    Ak pole obsahuje prvky, tak vrati ich maximum a nastavi 'result' na 'SUCCESS'.
    Ak pole neobsahuje ziadne prvky (jeho dlzka je nulova),
    tak vrati minimalnu hodnotu, ktoru moze reprezentovat datovy typ 'int' a nastavi result na 'FAILURE'.

    PARAMETRE:
        [in] data    - adresa zaciatku pola
        [in] length  - pocet prvkov pola (dlzka pola)
        [out] result - indikuje uspesnost najdena maxima

    NAVRATOVA HODNOTA:
        Ak pole obsahuje prvky, tak vrati hodnotu najvacsieho prvku pola 'data'.
        Ak pole neobsahuje prvky, tak vrati minimalnu hodnotu reprezentovatelnu datovym typom 'int'.

    PRIKLADY:
        vstup: (1, 2, 5, 0, 1) => navratova hodnota: 5,  result: 'Result::SUCCESS'
        vstup: (-5, -2, -10)   => navratova hodnota: -2, result: 'Result::SUCCESS'
        vstup: () => navratova hodnota: minimalna hodnota reprezentovatelna datovym typom 'int', result: 'Result::FAILURE'
*/
int maximum(const int *data, std::size_t length, Result *result) {
    if (length == 0) {
        *result = Result::FAILURE;  // TODO not working
        return INT_MIN;
    }

    int maxValue = data[0];
    for (size_t i = 1; i < length; i++) {
        if (data[i] > maxValue) {
            maxValue = data[i];
        }
    }
    *result = Result::SUCCESS;  // TODO not working
    return maxValue; 
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati pocet znakov, ktore su potrebne na zapis cisla 'value' (v desiatkovej ciselnej sustave).

    PARAMETER:
        - [in] value - analyzovana hodnota

    NAVRATOVA HODNOTA:
        Pocet znakov, potrebnych pre textovu reprezentaciu hodnoty 'value'

    PRIKLADY:
        - vstup: 18002 => vystup: 5
        - vstup: 2     => vystup: 1
        - vstup: 0     => vystup: 1
        - vstup: -500  => vystup: 4
*/
int numDigits(int value) {
    int sum = 0;
    if (value <= 0) {
        sum++;
        value = -value;
    }
    while (value > 0) {
        value /= 10;
        sum++;
    }
    return sum;
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytlaci na standardny vystup datum, podla zadaneho formatu.

    Vytlaceny text bude obsahovat kopiu textu vo 'format', ale
    znak 'D' nahradi dnom,
    znak 'M' nahradi mesiacom,
    znak 'Y' nahradi rokom v datume.

    PARAMETRE:
        - [in] date - datum
        - [in] format - format vylacenia datumu

    PRIKLADY:
        Nech datum je 10. aprila 2020
        - format: "D. M. Y" => "10. 4. 2020"
        - format: "D. M."   => "10. 4."
        - format: "Pisomka bude D. M. Y, v miestnosti BC 300" => "Pisomka bude 10. 4. 2020, v miestnosti BC 300"
        - format: "M/D/Y"   => "4/10/2020"
        - format: "Y-M-D"   => "2020-4-10"

    POZNAMKA:
        Vsimnite si pretazenie funkcie. Tento zdrojovy subor obsahuje 3 funkcie s nazvom 'print'.
*/
void print(const Date *date, const char *format) {
    string text = format;

    if (text.find("M") != string::npos) {
        text.replace(text.find("M"), 1, to_string(date->month));
    }

    if (text.find("D") != string::npos) {
        text.replace(text.find("D"), 1, to_string(date->day));
    }

    if (text.find("Y") != string::npos) {
        text.replace(text.find("Y"), 1, to_string(date->year));
    }

    cout << format << endl;
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy datum podla parametrov a vrati jeho adresu.
    Pre dynamicku alokaciu pamate pouzite operator 'new'.

    PARAMETRE:
        [in] day   - den v datume
        [in] month - mesiac v datume
        [in] year  - rok v datume

    NAVRATOVA HODNOTA:
        Adresa na dynamicky alokovany datum, ktoreho obsah je dany parametrami
*/
Date* create(int day, int month, int year) {
    Date *newDate = new Date;
    
    newDate->year = year;
    newDate->month = month;
    newDate->day = day;

    return newDate; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia dealokuje datum. Smernik na datum nastavi na 'nullptr'.
    Na dealokaciu pamate pouzite operator 'delete'.

    PARAMETER:
        [in, out] date - adresa smernika na datum

    VYSTUPNE PODMIENKY:
        Datum na adrese (*date) je dealokovany.
        (*date) ma hodnotu 'nullptr'.
*/
void destroy(Date **date) {
    if (*date != nullptr) {
        delete(*date);
        // cout << "pointer deleted";
    }
}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci je rok v datume priestupny.

    PARAMETER:
        [in] date - datum

    NAVRATOVA HODNOTA:
        'true'  - ak rok je priestupny
        'false' - ak rok nie je priestupny

    VSTUPNA PODMIENKA:
        Rok v datume je kladne cislo

    URCENIE PRIESTUPNEHO ROKU:
        Rok delitelny cislom 4 je priestupny okrem pripadu, ked je delitelny cislom 100, ale nie je delitelny cislom 400.
        Priklady:
            - priestupne roky: 2000, 2004, 2008
            - nepriestupne roky: 2001, 2002, 2003, 2005, 2006, 2007, 2009, 2010
            - priestupne roky: 1600, 2000, 2400
            - nepriestupne roky: 1500, 1700, 1800, 1900, 2100, 2200, 2300, 2500
*/
bool isInLeapYear(const Date *date) {
    int year = date->year;
    if (year % 400 == 0) {
        return true;
    } else if (year % 100 == 0) {
        return false;
    } else if (year % 4 == 0) {
        return true;
    } else {
        return false;
    }
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia zisti, ci je datum platny.

    Treba overit, ci datum moze existovat. Napriklad
    v januari moze byt den od 1 do 31,
    vo februari od 1 do 28 alebo 29, podla toho, ci je rok priestupny.
    Rok ma mesiac 1 az 12.

    PARAMETER:
        [in] date - datum

    NAVRATOVA HODNOTA:
        'true'  - ak datum je platny
        'false' - ak datum nie je platny

    VSTUPNA PODMIENKA:
        Rok v datume je kladne cislo
*/
bool isValid(const Date *date) {
    int year = date->year;
    int month = date->month;
    int day = date->day;

    if((month==1 || month==3 || month==5|| month==7|| month==8||month==10||month==12) && day>0 && day<=31)
        return true;

    if((month==4 || month==6 || month==9|| month==11) && (day>0 && day<=30))
        return true;

    if(month==2) {
        if((year%400==0 || (year%100!=0 && year%4==0)) && day>0 && day<=29)
            return true;
        else if(day>0 && day<=28)
            return true;
        else
            return false;
        }
    return false; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury


int main() {
    // Create examples of structs
    // Position samplePosition {
    //     30,  // X
    //     -25,  // y
    // };

    // Date sampleDate {
    //     2022,  // year
    //     9,  // month
    //     20,  // day
    // };  

    // Result enumResult;
    // int result;

    // int sampleData[8] = {-10, 0, 10, 12, 13, 55, 32, '\0'};

    // done 1.1 -> 0.4b
    // print(&samplePosition);

    // done 1.2 -> 0.4b
    // print(samplePosition);

    // done 1.3 -> 0.4b
    // readFromStandardInput(&samplePosition);
    // print(samplePosition);

    // done 1.4 -> 0.4b
    // int result = maximum(sampleData, 5, &enumResult);
    // cout << "Navratova hodnota: " << result << endl;

    // working-on 1.5 -> 0.3b
    // cout << numDigits(0) << endl;

    // not-done 1.6 -> 0.0b
    // Date *newDate01 = create(1, 3, 2000);

    // print(newDate01, "M/D/Y");
    // print(newDate01, "D. M. Y");
    // print(newDate01, "D. M.");
    // print(newDate01, "Pisomka bude D. M. Y, v miestnosti BC 300");

    // done 1.7 -> 0.4b
    // Date *tempDate;
    // tempDate = create(10, 4, 2002);
    // cout << tempDate->day << ". " << tempDate->month << ". " << tempDate->year << endl;

    // working-on 1.8 -> 0.2b
    // destroy(&tempDate);

    // done 1.9 -> 0.4b
    // Date *newDate01 = create(1, 1, 2000);
    // Date *newDate02 = create(1, 1, 2002);
    // Date *newDate03 = create(1, 1, 1600);
    // Date *newDate04 = create(1, 1, 1500);

    // cout << isInLeapYear(newDate01) << endl;
    // cout << isInLeapYear(newDate02) << endl;
    // cout << isInLeapYear(newDate03) << endl;
    // cout << isInLeapYear(newDate04) << endl;

    // done 1.10 -> 0.4b
    // Date *newDate01 = create(-1, 1, 2000);
    // Date *newDate02 = create(1, -1, 2002);
    // Date *newDate03 = create(29, 2, 1601);
    // Date *newDate04 = create(5, 6, 1520);
    // Date *newDate05 = create(29, 2, 1600);
    // Date *newDate06 = create(34, 5, 1500);
    // Date *newDate07 = create(32, 1, 1500);

    // cout << isValid(newDate01) << endl;
    // cout << isValid(newDate02) << endl;
    // cout << isValid(newDate03) << endl;
    // cout << isValid(newDate04) << endl;
    // cout << isValid(newDate05) << endl;
    // cout << isValid(newDate06) << endl;
    // cout << isValid(newDate07) << endl;


    // tu mozete doplnit testovaci kod

    return 0;
}
