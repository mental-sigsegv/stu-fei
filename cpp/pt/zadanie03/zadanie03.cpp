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
#include <cstring>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Uzol zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node* next; // smernik na dalsi uzol zoznamu
};

// Zretazeny zoznam
struct List {
    Node* first; // smernik na prvy uzol zoznamu
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada pole 'data' od najvacsieho prvku po najmensi prvok.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'length' moze mat lubovolnu hodnotu
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()
*/
void insertionSort(int *data, const size_t length) {
    if (length == 0 || length == 1) return;
    for (size_t i = 1; i < length; i++) {
        int index = i;
        while (data[index] > data[index-1]) {
            int tmp;
            tmp = data[index-1];
            data[index-1] = data[index];
            data[index] = tmp;
            index--;
            if (index < 0) {
                break;
            }
        }
    }

}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada textove retazce v poli 'data' od najvacsieho prvku po najmensi (lexikograficky).
    Preusporiadajte smerniky v poli.
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada.
                Pole obsahuje smerniky na textove retazce.
                Kazdy textovy retazec je ukonceny '\0'.
                Posledny smernik ma hodnotu 'nullptr'. Podla toho urcite pocet prvkov pola (pocet textovych retazcov).

    VSTUPNE PODMIENKY:
        'data' obsahuje minimalne jeden smernik.
        Posledny smernik ma hodnotu 'nullptr'.

    PRIKLADY:
        ("Juraj", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", nullptr)
        ("Juraj", "Anabela", "Peter", "Andrej", nullptr) -> ("Peter", "Juraj", "Andrej", "Anabela", nullptr)
        ("Andrej", "Juraj", "Andrej", nullptr) -> ("Juraj", "Andrej", "Andrej", nullptr)
        ("Andrej", nullptr) -> ("Andrej", nullptr)
        (nullptr) -> (nullptr)

    POZNAMKY:
        Pri testovani mozete jednoducho pole vytvorit nasledovnym sposobom:
        const char *mena[] = {"Juraj", "Peter", "Andrej", nullptr};

        Na porovnanie obsahu textovych retazcov vyuzite prislusnu funkciu zo standardnej kniznice.
*/
void insertionSort(const char *data[]) {
    if (data[0] == nullptr || data[1] == nullptr) return;
    strcmp("aa", "bz") > 0;

    size_t i = 1;
    while (data[i] != nullptr) {
        int index = i;
        while (strcmp(data[index], data[index-1]) > 0) {
            const char *tmp;
            tmp = data[index-1];
            data[index-1] = data[index];
            data[index] = tmp;
            index--;
            if (index <= 0) {
                break;
            }
        }
        i++;
    }

}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada zretazeny zoznam 'list' od najvacsieho prvku po najmensi.
    Preusporiadajte uzly v zozname (nekopirujte hodnoty v uzloch).
    Pouzite algoritmus insertion sort.

    PARAMETRE:
        [in, out] list - zretazeny zoznam, ktory funkcia usporiada

    VSTUPNE PODMIENKY:
        'list' obsahuje lubovolny pocet uzlov (moze byt prazdny)
        'list' nie je 'nullptr'

    PRIKLADY:
        vstup: 2->1->3,        vystup: 3->2->1
        vstup: 1->2->2->1,     vystup: 2->2->1->1
        vstup: prazdny zoznam, vystup: prazdny zoznam
*/
void insertionSort(List * list) {
    if (list->first == nullptr || list->first->next == nullptr) return;

    Node *pNode = list->first;
    Node *pNode2 = nullptr;
    Node *pNodeLast = nullptr;

    while (pNode != nullptr && pNode->next != nullptr) {
        cout << '-';
        Node *tmp;
        if (pNode == list->first && pNode->data > pNode->next->data) {
            tmp = list->first;
            list->first = list->first->next;
            tmp->next = list->first->next;
            list->first->next = tmp;
        } 
        
        if (pNodeLast != nullptr) {
            pNode2 = pNode;
            while (pNode2 != nullptr && pNode2->data < pNode2->next->data) {
                Node *tmp = pNode2;
                pNodeLast->next = tmp->next;
                tmp->next = pNodeLast->next->next;
                pNodeLast->next->next = tmp;

                pNodeLast=pNode2;
                pNode2 = pNode2->next;
            }
        }



        pNodeLast = pNode;
        pNode = pNode->next;
    }

}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vykona algoritmus merge (cast algoritmu merge sort), ktory ma linearnu vypoctovu zlozitost.
    Kombinuje dve susedne, usporiadane casti v poli 'input', do jednej usporiadanej casti v poli 'output'.
    Usporiadanie je od najvacsieho prvku po najmensi prvok!

    PARAMETRE:
        [out] output - vystupne pole, ktoreho cast output[low]...output[high-1] bude po vykonani funkcie usporiadana
        [in]  input  - vstupne pole, ktoreho casti input[low]...input[middle-1] a input[middle]...input[high-1]
                         musia byt pri volani funkcie usporiadane od najvacsieho prvku po najmensi
        [in]  low    - index 1. prvku lavej usporiadanej casti pola 'input'
        [in]  middle - index 1. prvku pravej usporiadanej casti pola 'input'
        [in]  high   - index za poslednym prvkom pravej usporiadanej casti pola 'input'

    VYSTUPNE PODMIENKY:
        Obsah 'input' je nezmeneny.
        output[low] ... output[high-1] obsahuje usporiadane prvky z input[low] ... input[high-1], zvysne prvky v 'output' funkcia nemeni.
        Prvky s indexami mensimi ako 'low' sa nemenia (ani v jednom poli).
        Prvky s indexami vacsimi alebo rovnymi ako 'high' sa nemenia (ani v jednom poli).

    PRIKLAD:
        low: 4
        middle: 8
        hight: 12
        input:                         (10, 10, 10, 10,  7,  5,  2,  0,  8,  4,  2,  1, 10, 10, 10, 10)
        output pred vykonanim funkcie: (20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20, 20)
        output po vykonani funkcie:    (20, 20, 20, 20,  8,  7,  5,  4,  2,  2,  1,  0, 20, 20, 20, 20)
*/
void mergeNeighbours(int *output, const int *input, const size_t low, const size_t middle, const size_t high) {
    // TODO
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia usporiada prvky v poli 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus merge sort.
    Vytvorte jedno pomocne pole. Pre alokaciu a dealokaciu pomocneho pola pouzite new[] a delete[].

    PARAMETRE:
        [in, out] data - pole, ktore funkcia usporiada
        [in] length    - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole

    PRIKLADY:
        (1, 3, 2) -> (3, 2, 1)
        (1, 2, 2, 1) -> (2, 2, 1, 1)
        (1) -> (1)
        () -> ()

    POZNAMKA:
        Ak pouzijete pristup top-down, tak
        - v tejto funkcii zabezpecte vytvorenie a kopirovanie dat do pomocneho pola,
        - vytvorte a zavolajte rekurzivnu funkciu, v ktorej implementujete hlavnu cast algoritmu merge sort.
*/
// void mergeSort(int *arrayA, int *arrayB, const size_t low, const size_t high) { // Priklad deklaracie rekurzivnej funkcie, v pripade pristupu top-down
// }
void mergeSort(int *data, const size_t length) {
    // TODO
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne funkcie a struktury

void printArray(const int *array, const size_t length) {
    for (size_t i = 0; i < length; i++) {
        cout  << array[i] << " ";
    }
    cout << "X" << endl;
}

void printArray(const char *data[]) {
    size_t i = 0;
    while (data[i] != nullptr) {
        cout << data[i] << " ";
        i++;
    }
    cout << "X" << endl;
}

void appendNode(List *list, const int val) {
    Node *appNode = new Node {val, nullptr};
    if (list->first == nullptr) {
        list->first = appNode;
        return;
    }

    Node *pNode = list->first;
    while(pNode->next != nullptr) {
        pNode = pNode->next;
    }
    pNode->next = appNode;
}

void printLinkedList(const List *list) {
    cout << "printing list" << endl;
    Node *pNode = list->first;
    while(pNode != nullptr) {
        cout << pNode->data << " ";
        pNode = pNode->next;
    }
    cout << endl;
}


int main() {
    // int *numsEmpty;
    // int numsOne[] = {1};
    // int nums01[] = {1,3,2};
    // int nums02[] = {1,2,2,1};

    // printArray(nums02, 6);

    // 3.1
    // insertionSort(numsEmpty, 0);
    // insertionSort(numsOne, 1);
    // insertionSort(nums01, 3);
    // insertionSort(nums02, 4);

    // printArray(numsEmpty, 0);
    // printArray(numsOne, 1);
    // printArray(nums01, 3);
    // printArray(nums02, 4);

    // 3.2
    // const char *mena01[] = {"Juraj", "Peter", "Andrej", nullptr};
    // const char *mena02[] = {"Juraj", "Anabela", "Peter", "Andrej", nullptr};
    // const char *mena03[] = {"Andrej", "Juraj", "Andrej", nullptr};
    // const char *mena04[] = {"Andrej", nullptr};

    // insertionSort(mena01); 
    // insertionSort(mena02); 
    // insertionSort(mena03); 
    // insertionSort(mena04); 

    // printArray(mena01);
    // printArray(mena02);
    // printArray(mena03);
    // printArray(mena04);

    // 3.3
    struct List *list = new List {nullptr};
    appendNode(list, 1);
    appendNode(list, 2);
    appendNode(list, 2);
    appendNode(list, 1);

    printLinkedList(list);
    insertionSort(list);
    printLinkedList(list);

    // 3.4
    // 3.5
    return 0;
}
