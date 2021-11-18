from pprint import pprint

class player():
    def __init__(self, size_of_board, name):
        self.name = name
        self.size_of_board = size_of_board
        self.DLZKA_DOMCEKA = DLZKA_DOMCEKA
        self.panacikovia = {f'{self.name}{i}':None for i in range(1, self.DLZKA_DOMCEKA+1)}
        self.starting_point = 0 if self.name == 'A' else (size_of_board-1)*2

    def get_position(self):
        return self.panacikovia

def pravidla_hry():
    rules = [
        "Ak nema hrac ziadneho panacika na hracej ploche, hadze 3x alebo pokial nehodi 6tku",
        "Ak hrac stupi na panacika ineho hraca (alebo aj na svojho), vybije ho a teda panacik ineho hraca (alebo seba sameho) sa vrati do stajne",
        "Kazdy hrac ma na zaciatku rovnaky pocet panacikov v stajni ako je pocet domcekov"
        "Vitazom za stava hrac, kt. prvy dostane vsetky svoje figurky do domceka",
        "Ak hrac hodi 6tku, ma pravo na dalsi hod",
    ]
    for i, text in enumerate(rules):
        print(f"{i+1}. pravidlo - {text}")
# pravidla_hry()

def update_matrix(matrix, n, array):
    s = MATRIX_STRED
    d = DLZKA_DOMCEKA
    n -= 1
    matrix[1][s-1:s+2] = array[-2:]+[array[0]]
    matrix[-1][s-1:s+2] = [array[n*2]]+array[n*2-1:n*2-3:-1]
    matrix[s][1] = array[3*n-1]
    matrix[s][-1] = array[n-1]
    for i in range(n//2-1):
        matrix[i+2][s+1] = array[i+1]
        matrix[i+2][s-1] = array[-i-3]
        matrix[i+3+d][s+1] = array[n+d+i]
        matrix[i+3+d][s-1] = array[2*n+d-i]

        matrix[s-1][s+2+i] = array[n//2+i]
        matrix[s-1][s-2-i] = array[3*n+n//2-2-i]
        matrix[s+1][s+2+i] = array[n+n//2-i-2]
        matrix[s+1][s-2-i] = array[2*n+n//2+i]
    return matrix

def setup_matrix(n):
    matrix =  [[" "] + [str(i)[-1] for i in range(n)]] + [[str(i)[-1]]+[" " for _ in range(n)] for i in range(n)] #zakladny matrix
    s = MATRIX_STRED  #stred matrixu

    # nastavenie domcekov na "D" a stredu na "X"
    for d in range(1, DLZKA_DOMCEKA+1):
        matrix[s][s+d] = "D"    #domceky na pravo od stredu
        matrix[s][s-d] = "D"    #domceky na lavo od stredu
        matrix[s+d][s] = "D"    #domceky na hore od stredu
        matrix[s-d][s] = "D"    #domceky na dole od stredu
    matrix[s][s] = "X"

    array = ['*' for i in range((n-1)*4)]
    matrix = update_matrix(matrix, n, array)

    return matrix

def gensachovnicu(n):   #Vygeneruje matrix + aj jeho indexy osi x, y (hore, vlavo)
    # podmienky matrixu
    if not isinstance(n, int):
        return f"Vstup ma byt typu integer (bolo zadane {type(n)})"
    elif n < 0:
        return f"Vstup ma byt kladne cislo (bolo zadane {n})"
    elif n % 2 == 0:
        return f"Vstup ma byt neparne cislo (bolo zadane {n})"
    elif n < 5:
        return f"Vstup ma byt vacsi ako 5 (bolo zadane {n})"
    matrix = setup_matrix(n)
    return matrix


def tlacsachovnicu(n):
    matrix = gensachovnicu(n)
    if isinstance(matrix, str):
        print(matrix)
    else:
        for row in matrix:
            print(' '.join(row))

def game(n):
    global DLZKA_DOMCEKA
    global MATRIX_STRED
    DLZKA_DOMCEKA = n//2-1
    MATRIX_STRED = n//2+1

    i = 0
    hracA = player(n, "A")
    while i < 5:
        print('-'*43)
        tlacsachovnicu(n)
        i += 1


def main():
    pravidla_hry()
    print('-'*43)
    game(11)
    # print('-'*43)
    # tlacsachovnicu(13)
    # print('-'*43)
    # tlacsachovnicu(15)
    # print('-'*43)
main()