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

using namespace std;

//-------------------------------------------------------------------------------------------------
// 1. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia prida novy prvok do heapu.
    Verzia heap-u je Min-heap (hodnota kazdeho uzla je mensia alebo rovna, ako hodnoty vsetkych jeho nasledovnikov).
    Pouzite algoritmus sift up.

    PARAMETRE:
        [in, out] data - pole, ktoreho prva cast tvori heap, do ktoreho funkcia prida novy prvok
        [in] addIndex - index prvku v 'data', ktory funkcia prida do heap-u (preusporiadanim prvkov)

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole s dlzkou minimalne 'addIndex+1'
        'addIndex' moze mat lubovolnu hodnotu
        Prvky data[0]...data[addIndex-1] (vratane) tvoria heap

    VYSTUPNE PODMIENKY:
        Prvky data[0]...data[addIndex] (vratane) tvoria heap
        Funkcia preusporiadala prvky data[0]...data[addIndex] tak, aby tvorili heap

    PRIKLADY:
        vstup:  data = (2, 4, 10, 7, 1, 2, 5, 0, 3, -1, 11, 12, 1), addIndex = 4
        vystup: data = (1, 2, 10, 7, 4, 2, 5, 0, 3, -1, 11, 12, 1)

        vstup:  data = (3, 4, 10, 5, 5, 11, 15, 7, 8, 9, 10, 14,  8, 1, 2), addIndex = 12
        vystup: data = (3, 4,  8, 5, 5, 10, 15, 7, 8, 9, 10, 14, 11, 1, 2)

        vstup:  data = (3, 4, 10, 5), addIndex = 0
        vystup: data = (3, 4, 10, 5)
*/

void print(int data[], int length) {
    for (int i=0; i< length; i++) {
        cout << data[i] << " ";
    }
    cout << endl;
}


void swap(int data[], const int indexA, const int indexB) {
    int tmp = data[indexA];
    data[indexA] = data[indexB];
    data[indexB] = tmp;
}

void siftUp(int data[], const size_t addIndex) {
    int currentIndex = addIndex;
    if (currentIndex == 0) return;

    while (currentIndex > 0) {
        int previousIndex = (currentIndex+1)/2 - 1;
        if (data[currentIndex] >= data[previousIndex]) return;
        swap(data, currentIndex, previousIndex);
        currentIndex = previousIndex;
    }
}

//-------------------------------------------------------------------------------------------------
// 2. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori heap na poli 'data' preusporiadanim prvkov.
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift up.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia preusporiada, aby bolo heap-om
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        'data' je heap-om

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (1, 2, 2, 2, 2, 5, 3, 7, 4, 8, 6)
*/
void buildHeapSiftUp(int data[], const size_t length)
{
    for (size_t i = 0; i<length; i++) {
        siftUp(data, i);
    }
}

//-------------------------------------------------------------------------------------------------
// 3. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia opravi cast heap-u (podstrom, ktoreho koren ma index 'topIndex').
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift down.

    PARAMETRE:
        [in, out] data - pole, v ktorom funkcia opravi cast heapu preusporiadanim prvkov
        [in] topIndex - index korena podstromu (casti heapu), ktory sa ma opravit
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        Podstromy prvku s indexom 'topIndex' splnaju podmienky heap (podstromy, ktorych korene su priamy nasledovnici uzla s indexom 'topIndex').
        'data' ukazuje na platne pole
        'topIndex' moze mat lubovolnu hodnotu
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        Podstrom, ktoreho koren ma index 'topIndex', splna podmienku heap.

    PRIKLADY:
        vstup:  data = (55, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140), topIndex = 0, length = 15
        vystup: data = (10, 20, 50, 30, 40, 55, 60, 70, 80, 90, 100, 110, 120, 130, 140)

        vstup:  data = (100, 8, 2, 1, 0, 5, 6, 7, 4, 2, 3, 11, 12, 13, 14, 15, 16, 17), topIndex = 1, length = 18
        vystup: data = (100, 0, 2, 1, 2, 5, 6, 7, 4, 8, 3, 11, 12, 13, 14, 15, 16, 17)
*/

bool isLower(int data[], int child, int parent) {
    if ((data[child] < data[parent]) || (data[child+1] < data[parent])) return true;
    return false;
}

int getLowerIndex(const int data[], int child) {
    return (data[child] < data[child+1]) ? child : child+1;
}

bool isParentBranch(int parent, int topIndex) {
    while (parent > topIndex) {
        parent /= 2;
    }
    return (parent == topIndex) ? true : false;
}

void siftDown(int data[], const size_t topIndex, const size_t length)
{
    for (size_t parent = topIndex; parent < length; parent++) {
        if (isParentBranch(parent, topIndex)) {
            while ((parent+1)*2-1 < length) {
                size_t leftChild = (parent+1)*2 - 1;
                size_t rightChild = (parent+1)*2;

                if ((rightChild < length) && isLower(data, leftChild, parent)) {
                    swap(data, parent, getLowerIndex(data, leftChild));
                    parent = getLowerIndex(data, leftChild);
                } else if (data[leftChild] < data[parent]) {
                    swap(data, leftChild, parent);
                    parent = leftChild;
                } else {
                    break;
                }
            }
        }
    }
}

//-------------------------------------------------------------------------------------------------
// 4. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia vytvori heap na poli 'data' preusporiadanim prvkov.
    Verzia heap-u je Min-heap.
    Pouzite algoritmus sift down.

    PARAMETRE:
        [in, out] data - pole, ktore funkcia preusporiada, aby bolo heap-om
        [in] length - pocet prvkov pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        'data' je heap-om

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (1, 2, 3, 2, 2, 5, 7, 4, 2, 8, 6)
*/
void buildHeapSiftDown(int data[], const size_t length)
{
    for (size_t i = 0; i < length; i++) {
        siftDown(data, i, length);
    }
}

//-------------------------------------------------------------------------------------------------
// 5. ULOHA (0.8 bodu)
//-------------------------------------------------------------------------------------------------
/*
    Funkcia preusporiada pole 'data' od najvacsieho prvku po najmensi.
    Pouzite algoritmus heap sort.

    PARAMETRE:
        [in,out] data - pole, ktore funkcia usporiada
        [in] length - dlzka pola

    VSTUPNE PODMIENKY:
        'data' ukazuje na platne pole, ak 'length' > 0
        'length' moze mat lubovolnu hodnotu

    VYSTUPNE PODMIENKY:
        Pole 'data' je usporiadane

    PRIKLAD:
        vstup:  data = (7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6), length = 11
        vystup: data = (8, 7, 6, 5, 4, 3, 2, 2, 2, 2, 1)
*/


void heapSort(int data[], const size_t length)
{
    return;
}

//-------------------------------------------------------------------------------------------------
// TESTOVANIE
//-------------------------------------------------------------------------------------------------

// tu mozete doplnit pomocne testovacie funkcie a struktury

int main() {
    // done 5.1 -> 0.8b
    // int data01[] = {2, 4, 10, 7, 1, 2, 5, 0, 3, -1, 11, 12, 1};
    // int data02[] = {3, 4, 10, 5, 5, 11, 15, 7, 8, 9, 10, 14,  8, 1, 2};
    // int data03[] = {3, 4, 10, 5};

    // siftUp(data01, 4);
    // siftUp(data02, 12);
    // siftUp(data03, 0);

    // print(data01, 13);
    // print(data02, 15);
    // print(data03, 4);

    // done 5.2 -> 0.8b
    // int data04[] = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6};

    // buildHeapSiftUp(data04, 11);

    // print(data04, 11);

    // working-on 5.3 -> 0b
    int data05[] = {55, 20, 10, 30, 40, 50, 60, 70, 80, 90, 100, 110, 120, 130, 140};
    int data06[] = {100, 8, 2, 1, 0, 5, 6, 7, 4, 2, 3, 11, 12, 13, 14, 15, 16, 17};

    siftDown(data05, 0, 15);
    siftDown(data06, 1, 18);

    print(data05, 15);
    print(data06, 18);
    
    // working-on 5.4 -> 0b
    // int data07[] = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6};

    // buildHeapSiftDown(data07, 11);

    // print(data07, 11);

    // not-done 5.5
    // int data08[] = {7, 2, 1, 2, 8, 5, 3, 4, 2, 2, 6};
    
    // heapSort(data08, 11);
    
    // print(data08, 11);

    return 0;
}
