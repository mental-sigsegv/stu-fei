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
#include <stack>

using namespace std;

//-------------------------------------------------------------------------------------------------
// DATOVE TYPY
//-------------------------------------------------------------------------------------------------

// Reprezentacia uzla zretazeneho zoznamu
struct Node {
    int data; // hodnota uzla
    Node *next; // adresa nasledujuceho uzla zoznamu
};

// Reprezentacia zretazeneho zoznamu
struct List {
    Node *first; // adresa prveho uzla zoznamu
};

// Pomocna struktura pre ulohu 2
struct ListData {
    int *data; // pole hodnot uzlov
    size_t len; // dlzka pola 'data'
};

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' na koniec zretazeneho zoznamu 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr') a moze
           mat lubovolny pocet uzlov (0 a viac).

    PARAMETRE:
        [in, out] list - adresa zretazeneho zoznamu, do ktoreho ideme pridavat uzol
        [in] val       - hodnota uzla, ktory sa ma pridat na koniec zoznamu 'list'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        prazdny zoznam, 5 ---> (5)
        (1), 1 ---> (1,1)
        (8,2,6,6), 14 ---> (8,2,6,6,14)
        (6,100,33), -85 ---> (6,100,33,-85)
        (1,2,3,4,5), 3 ---> (1,2,3,4,5,3)
*/

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

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zretazeny zoznam, ktory bude skonstruovany pomocou udajov vo vstupnej
    strukture 'listData'. Struktura 'listData' obsahuje polozku 'data', ktora reprezentuje pole
    hodnot pre jednotlive uzly zoznamu. Struktura 'listData' taktiez obsahuje polozku 'len', ktora
    hovori aku ma dlzku pole 'data'. Vytvoreny zoznam musi obsahovat uzly, ktore zodpovedaju
    svojimi hodnotami a poradim prvkom ulozenym v poli 'data' (dlzka zoznamu bude 'len').
    Funkcia nakoniec vrati adresu takto vytvoreneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'listData' vzdy existuje (t.j. 'listData' je rozny od 'nullptr').
        2) Pre polozku 'len' plati, ze 'len' >= 0 a nikdy nebude mat vacsiu hodnotu ako je
           realny pocet prvkov v poli 'data'.
    VYSTUPNA PODMIENKA:
        1) Ak je polozka 'len' rovna 0, vtedy sa vytvori a vrati prazdny zretazeny zoznam
           (t.j. platny zoznam, ktory ma 0 uzlov).

    PARAMETRE:
        [in] listData - struktura, pomocou ktorej sa vytvori zoznam

    NAVRATOVA HODNOTA:
        Adresa zretazeneho zoznamu, ktory bol vytvoreny pomocou struktury 'listData'.
        Vid pokyny vyssie.

    PRIKLADY:
        polozka 'data' = (1,2,3)
        polozka 'len' = 0
        vystupny zoznam bude mat 0 uzlov, t.j. ()

        polozka 'data' = (1,2,3)
        polozka 'len' = 2
        vystupny zoznam bude (1,2)

        polozka 'data' = (1,2,3)
        polozka 'len' = 3
        vystupny zoznam bude (1,2,3)

        polozka 'data' = (-9,412,64,72,100,100,6)
        polozka 'len' = 4
        vystupny zoznam bude (-9,412,64,72)
*/

List *createList(const ListData *listData) {
    struct List *newList = new List {nullptr};
    Node *pNode = nullptr;
    
    if (listData->len == 0) {
        return newList;
    }

    newList->first = new Node {listData->data[0], nullptr};
    pNode = newList->first;

    for (size_t i = 1; i < listData->len; i++) { 
        pNode->next = new Node {listData->data[i], nullptr};
        pNode = pNode->next;
    }

    return newList;
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy uzol s hodnotou 'val' do vzostupne zotriedeneho zoznamu 'sortedList'.
    Pridanie musi prebehnut takym sposobom, aby bol zoznam 'sortedList' po pridani noveho uzla
    stale vzostupne zotriedeny.

    POZNAMKA: Na poradi duplikatov v zozname 'sortedList' nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'sortedList' vzdy existuje (t.j. 'sortedList' je rozny od 'nullptr').
        2) Vstupny zoznam 'sortedList' moze mat lubovolny pocet uzlov (0 a viac).
        3) Vstupny zoznam 'sortedList' je vzostupne zotriedeny.

    PARAMETRE:
        [in, out] sortedList   - adresa vstupneho zretazeneho zoznamu, ktory je zotriedeny
                                 vzostupne (z angl. ascending)
        [in] val               - hodnota uzla, ktory sa ma pridat do zoznamu 'sortedList'

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        (), 0 ---> (0}
        (), 156 ---> (156)
        (8), 4 ---> (4,8)
        (7), 10 ---> (7,10)
        (55), 55 ---> (55,55) ... poznamka: na poradi duplikatov nezalezi
        (1,8,236,888), 70 ---> (1,8,70,236,888)
        (5,5,14,82,82,100), 5 ---> (5,5,5,14,82,82,100)
*/

void insertNode(List *sortedList, const int val) {
    Node *pNodeValue = new Node {val, nullptr};
    Node *pNode = nullptr;

    if (sortedList->first == nullptr || val < sortedList->first->data) {
        pNodeValue->next = sortedList->first;
        sortedList->first = pNodeValue;
        return;
    } else if (sortedList->first->next == nullptr) {
        if (val >= sortedList->first->data) {
            sortedList->first->next = pNodeValue;
            return;
        } else {
            pNodeValue->next = sortedList->first;
            sortedList->first = pNodeValue;
            return;
        }
    }
    pNode = sortedList->first;

    while (pNode->next != nullptr) {
        if (pNode->data <= val && val <= pNode->next->data) {
            pNodeValue->next = pNode->next;
            pNode->next = pNodeValue;
            return;
        }
        pNode = pNode->next;
    }
    pNode->next = pNodeValue;


}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori novy zoznam spojenim zoznamov 'list1' a 'list2'. Funkcia vrati adresu
    novo vytvoreneho zoznamu. V spojenom zozname idu najprv uzly zoznamu 'list1' (v nezmenenom poradi)
    a potom nasleduju uzly zoznamu 'list2' (v nezmenenom poradi). Pri vytvarani noveho zoznamu mozete
    pouzit hlboku alebo plytku kopiu existujucich uzlov (obe riesenia budu akceptovane).

    POZNAMKA:
        Prazdny zoznam je taky zoznam, ktory je platny, ale obsahuje 0 uzlov
        (t.j. polozka 'first' je nastavena na 'nullptr').

    VSTUPNE PODMIENKY:
        1) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).

    PARAMETRE:
        [in, out] list1 - adresa prveho zoznamu
        [in, out] list2 - adresa druheho zoznamu

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol spojenim zoznamov 'list1' a 'list2'.

    PRIKLADY:
        () + () ---> ()
        (5,9) + () ---> (5,9)
        () + (2,2,2) ---> (2,2,2)
        (1) + (2) ---> (1,2)
        (7) + (3,9,16) ---> (7,3,9,16)
        (50,-47,23,1) + (0,0,9,-8) ---> (50,-47,23,1,0,0,9,-8)
*/

List *joinLists(List *list1, List *list2) {
    if (list1->first == list2->first && list1->first == nullptr) {
        return list1;
    }

    Node *pNode = list1->first;
    if (pNode == nullptr) {
        list1->first = list2->first;
        return list1;
    }
    while (pNode->next != nullptr) {
        pNode = pNode->next;
    }
    pNode->next = list2->first;

    return list1; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia odstrani posledny uzol zo zoznamu 'list'. Ak je zoznam 'list' prazdny, funkcia nic
    nevykona. Pamat uzla, ktory funkcia vymaze musi byt korektne dealokovana.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in, out] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Ziadna.

    PRIKLADY:
        () ---> ()
        (1) ---> ()
        (1,2) ---> (1)
        (1,2,3) ---> (1,2)
*/

void removeLastNode(List *list) {
    if (list->first == nullptr) {
        return;
    } else if (list->first->next == nullptr) {
        list->first = nullptr;
        return;
    }

    Node *pNode = list->first;

    while (pNode->next->next != nullptr) {
        pNode = pNode->next;
    }
    free(pNode->next->next);
    pNode->next = nullptr;    
}

//-------------------------------------------------------------------------------------------------
// 6. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci je vstupny zoznam 'list' palindrom. Prazdny zoznam budeme povazovat za
    palindrom.

    Poznamka: Palindrom predstavuje taku postupnost hodnot, ktora sa cita rovnako v oboch smeroch.
    URL: https://sk.wikipedia.org/wiki/Palindr%C3%B3m
    Priklad palindromu: 1212121 alebo 4953594

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa vstupneho zoznamu

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci vstupny zoznam je/nie je palindrom.

    PRIKLADY:
        () ---> true
        (1) ---> true
        (2,2,2,2) ---> true
        (1,2,3,4,5) ---> false
        (1,2,2,1) ---> true
        (8,4,8,4,8) ---> true
        (9,842,613,2,613,842,9) ---> true
        (7,9,1,2) ---> false
        (0,0,0,7,0,0) ---> false
*/

bool isPalindrome(const List *list) {
    if (list->first == nullptr || list->first->next == nullptr) {
        return true;
    }

    Node *pNode = list->first;
    stack <int> iStack;
    while (pNode->next != nullptr) {
        pNode = pNode->next;
        iStack.push(pNode->data);
    }

    pNode = list->first;
    while (pNode->next != nullptr) {
        int mostTop = iStack.top();
        iStack.pop();
        if (mostTop != pNode->data) {
            return false;
        }
        pNode = pNode->next;
    }


    return true;
}

//-------------------------------------------------------------------------------------------------
// 7. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vrati sucet hodnot prvych 'n' uzlov v zozname 'list'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. 'list' je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).
        3) Parameter 'n' nebude zaporny a nebude mat nikdy vyssiu hodnotu ako je realny pocet
           uzlov v zozname.

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] n - pocet uzlov od zaciatku zoznamu 'list', ktorych sucet sa vrati

    NAVRATOVA HODNOTA:
        Sucet hodnot prvych 'n' uzlov zoznamu 'list'. Ak 'n'=0, vtedy funkcia vrati hodnotu 0.

    PRIKLADY:
        (), 0 ---> 0
        (1,2,3), 0 ---> 0
        (6), 1 ---> 6
        (5,6,7), 2 ---> 11
        (4,4,4,4,4,4), 6 ---> 24
        (-8,41,-314,21), 3 ---> -281
*/

int sumNodes(const List *list, const size_t n) {
    if (n == 0) return 0;

    Node *pNode = list->first;
    int sum = 0;
    for (size_t i=0; i < n; i++) {
        sum += pNode->data;
        pNode = pNode->next;
    }
    return sum;
}

//-------------------------------------------------------------------------------------------------
// 8. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia overi, ci zoznam 'list1' obsahuje vsetky hodnoty uzlov zoznamu 'list2'.
    Na poradi nezalezi.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list1' a 'list2' vzdy existuju (t.j. su rozne od 'nullptr').
        2) Zoznamy 'list1' a 'list2' mozu byt lubovolne dlhe (0 a viac uzlov).
        3) Zoznam 'list2' nebude obsahovat duplicitne uzly.

    PARAMETRE:
        [in] list1 - prvy zoznam
        [in] list2 - druhy zoznam

    NAVRATOVA HODNOTA:
        Pravdivostna hodnota 'true'/'false' podla toho, ci zoznam 'list1' obsahuje/neobsahuje
        vsetky hodnoty uzlov zoznamu 'list2'.

    PRIKLADY:
        (), () ---> true
        (), (1,2,3) ---> false
        (1,2,3), () ---> true
        (5,6,7), (5,6,8) ---> false
        (8,4,3), (3,8,4) ---> true
        (7,6,1,9,8), (1,6,8) ---> true
        (3,3,3,3,3), (2,3) ---> false
        (8,6,1,2,5,0,7,7), (7) ---> true
        (9,5,10), (41,10,5) ---> false
*/

bool contains(const List *list1, const List *list2) {
    if (list2->first == nullptr) {
        return true;
    }
    Node *pNode2 = list2->first;
    while (pNode2 != nullptr) {
        bool flag = false;
        Node *pNode1 = list1->first;

        while (pNode1 != nullptr) {
            if (pNode2->data == pNode1->data) {
                flag = true;
            }
            pNode1 = pNode1->next;
        }

        pNode2 = pNode2->next;
        if (flag == false) {
            return false;
        }
    }
    return true;

}

//-------------------------------------------------------------------------------------------------
// 9. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori a vrati HLBOKU kopiu zoznamu 'list'. Vo vytvorenej kopii musia byt zachovane
    hodnoty a poradie uzlov z povodneho zoznamu.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - adresa zoznamu, ktoreho hlboku kopiu treba vytvorit

    NAVRATOVA HODNOTA:
        Adresa zoznamu, ktory vznikol ako hlboka kopia vstupneho zoznamu 'list'. Kopiou
        prazdneho zoznamu je prazdny zoznam.

    PRIKLADY:
        Vstup = ()
        Vystup = ()

        Vstup = (1,2,3)
        Vystup = (1,2,3)
        Poznamka: adresy uzlov na rovnakych poziciach v oboch zoznamoch sa musia lisit
        (pretoze je to hlboka kopia)
*/

List *deepCopyList(const List *list) {
    List *nList = new List {nullptr};

    if (list->first == nullptr) {
        return nList;
    }

    Node *pNode = list->first;

    Node *pNode2 = nList->first;

    Node *pLastNode = nullptr;

    Node *pHeadNode = nullptr;

    while (pNode != nullptr) {
  

        pNode2 = new Node {pNode->data, nullptr};

        if (pHeadNode == nullptr) {
            pHeadNode = pNode2;
        }

        if (pLastNode != nullptr) {
            pLastNode->next = pNode2;
        }
        pLastNode = pNode2;

        pNode = pNode->next;
    }
    nList->first = pHeadNode;
    return nList; // tento riadok zmente podla zadania, je tu len kvoli kompilacii
}

//-------------------------------------------------------------------------------------------------
// 10. ULOHA (0.4 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia najde posledny vyskyt uzla s hodnotou 'val' v zozname 'list' a vrati jeho adresu.
    Ak sa v zozname 'list' takyto uzol nenachadza, funkcia vrati 'nullptr'.

    VSTUPNE PODMIENKY:
        1) Plati, ze 'list' vzdy existuje (t.j. je rozny od 'nullptr').
        2) Zoznam 'list' moze byt lubovolne dlhy (0 a viac uzlov).

    PARAMETRE:
        [in] list - vstupny zretazeny zoznam
        [in] val - hladana hodnota uzla

    NAVRATOVA HODNOTA:
        Adresa posledneho vyskytu uzla s hodnotou 'val' v zozname 'list'.

    PRIKLADY (treba otestovat pomocou debuggera):
        (), 2 ---> nullptr
        (5,4,3,2), 1 ---> nullptr
        (-5,4,-9,66), 4 ---> adresa 2. uzla
        (1,1,1,5,6,41), 1 ---> adresa 3. uzla
        (8,6,7,3,2,6), 6 ---> adresa 6. uzla
*/

Node *findLastNodeOccurrence(const List *list, const int val) {
    if (list->first == nullptr) return nullptr;

    Node *pNode = list->first;
    Node *lastNode = nullptr;


    while (pNode->next != nullptr) {
        if (pNode->data == val) {
            lastNode = pNode;
        }
        pNode = pNode->next;
    }
    if (pNode->data == val) {
        lastNode = pNode;
    }

    return lastNode;

}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

void printLinkedList(const List *list) {
    cout << "printing list" << endl;
    Node *pNode = list->first;
    while(pNode != nullptr) {
        cout << pNode->data << ", ";
        pNode = pNode->next;

    }
}

// tu mozete doplnit pomocne testovacie funkcie a struktury



int main() {
    struct List *list = new List {nullptr};
    // struct List *list2 = new List {nullptr};
    
    // done 2.1. -> 0.4b
    // appendNode(list, 15);
    // printLinkedList(list);

    // done 2.2 -> 0.4b
    // int numbers[] = {1,2,3,4,5,6,7};
    // struct ListData *listData = new ListData {numbers, 5};

    // struct List *list = createList(listData);
    // printLinkedList(list);
    
    // done 2.3 -> 0.4b
    // appendNode(list, 2);
    // appendNode(list, 11);
    // appendNode(list, 15);
    // appendNode(list, 18);
    // appendNode(list, 23);
    // insertNode(list, 105);
    // printLinkedList(list);

    // done 2.4 -> 0.4b
    // appendNode(list, 10);
    // appendNode(list, 20);
    // appendNode(list, 30);
    // appendNode(list2, 40);
    // appendNode(list2, 50);
    // appendNode(list2, 60);

    // printLinkedList(joinLists(list, list2));

    // done 2.5 -> 0.4b
    // appendNode(list, 10);
    // appendNode(list, 12);
    // appendNode(list, 13);
    // appendNode(list, 14);
    // appendNode(list, 10);
    // removeLastNode(list);
    // printLinkedList(list);

    // done 2.6 -> 0.4b
    // appendNode(list, 10);
    // appendNode(list, 15);
    // appendNode(list, 12);
    // cout << isPalindrome(list);

    // done 2.7 -> 0.4b
    // appendNode(list, 10);
    // appendNode(list, 10);
    // appendNode(list, 10);
    // appendNode(list, 10);
    // appendNode(list, 10);
    // cout << sumNodes(list, 5);

    // done 2.8 -> 0.4b
    // appendNode(list, 1);
    // appendNode(list, 2);
    // appendNode(list, 3);
    // appendNode(list, 4);

    // appendNode(list2, 3);
    // appendNode(list2, 4);

    // cout << contains(list, list2);

    // done 2.9 -> 0.4b
    // appendNode(list, 2);
    // appendNode(list, 3);
    // appendNode(list, 4);
    // appendNode(list, 4);
    // appendNode(list, 4);
    // appendNode(list, 4);
    // appendNode(list, 4);


    // List *list2 = deepCopyList(list);

    // cout << &list << endl;
    // cout << &list2 << endl;
    
    // done 2.10 -> 0.4b
    // appendNode(list, 1);
    // appendNode(list, 2);
    // appendNode\(list, 2);
    // appendNode(list, 2);

    // cout << findLastNodeOccurrence(list, 2);
    return 0;
}
