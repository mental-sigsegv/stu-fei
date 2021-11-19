from random import randint

class Board():
    def __init__(self):
        self.n = size_of_board
        self.matrix = []
        self.array = ['()' for _ in range((self.n-1)*4)]
        self.gen_board()
        self.print_board()

    def gen_board(self):
        self.matrix = [["  "] + [str(i)[-1]+' ' if i < 10  else str(i)[-2:] for i in range(self.n)]] + [[' '+str(i)[-1] if i < 10  else str(i)[-2:]]+["  " for _ in range(self.n)] for i in range(self.n)] #zakladny matrix
        s = MATRIX_STRED  #stred matrixu

        # nastavenie domcekov na "D" a stredu na "X"
        for d in range(1, DLZKA_DOMCEKA+1):
            self.matrix[s][s+d] = "DD"    #domceky na pravo od stredu
            self.matrix[s][s-d] = "DD"    #domceky na lavo od stredu
            self.matrix[s+d][s] = "DD" #self.hracAdomcek[d-1]    #domceky na hore od stredu
            self.matrix[s-d][s] = "DD" #self.hracBdomcek[d-1]    #domceky na dole od stredu
        self.matrix[s][s] = "XX"

    def update_board(self):
        s, d = MATRIX_STRED, DLZKA_DOMCEKA
        array, n, matrix = self.array, self.n - 1, self.matrix

        #priradenie matrixovym suradniciam array hodnoty
        matrix[1][s-1:s+2] = array[-2:]+[array[0]]
        matrix[-1][s-1:s+2] = [array[n*2]]+array[n*2-1:n*2-3:-1]
        matrix[s][1] = array[3*n-1]
        matrix[s][-1] = array[n-1]

        for i in range(d):
            matrix[i+2][s+1] = array[i+1]
            matrix[i+2][s-1] = array[-i-3]
            matrix[i+3+d][s+1] = array[n+d+i]
            matrix[i+3+d][s-1] = array[2*n+d-i]

            matrix[s-1][s+2+i] = array[n//2+i]
            matrix[s-1][s-2-i] = array[3*n+n//2-2-i]
            matrix[s+1][s+2+i] = array[n+n//2-i-2]
            matrix[s+1][s-2-i] = array[2*n+n//2+i]

        #priradenie matrixovym suradniciam domcekove hodnoty z classu player
        for i in range(d):
            matrix[s-i-1][s] = player_A.home[i]
            matrix[s+i+1][s] = player_C.home[i]
        matrix[s][s+1:s+1+d] = player_B.home
        matrix[s][s-d:s] = player_D.home


    def print_board(self):
        self.update_board()
        for row in self.matrix:
            print(' '.join(row))
        print('-'*45)


class Player():
    def __init__(self, name):
        self.home = [f'{name}'*2 for _ in range(DLZKA_DOMCEKA)]
        self.name = name

def pravidla_hry():
    print('-'*15+' PRAVIDLA HRY '+'-'*16)
    rules = [
        "Ak nema hrac ziadneho panacika na hracej ploche, hadze 3x alebo pokial nehodi 6tku",
        "Ak hrac stupi na panacika ineho hraca (alebo aj na svojho), vybije ho a teda panacik ineho hraca (alebo seba sameho) sa vrati do stajne",
        "Kazdy hrac ma na zaciatku rovnaky pocet panacikov v stajni ako je pocet domcekov"
        "Vitazom za stava hrac, kt. prvy dostane vsetky svoje figurky do domceka",
        "Ak hrac hodi 6tku, ma pravo na dalsi hod",
    ]
    for i, text in enumerate(rules):
        print(f"{i+1}. pravidlo - {text}")

if __name__ == '__main__':

    # print('Vitaj')
    # pravidla_hry()
    # print('-'*45)
    # print()

    # urcit pocet hracov
    # print('Zvolte si pocet hracov od 1 do 4')
    # while True:
    #     try:
    #         num_of_players = input()
    #         if num_of_players == '':
    #             raise ValueError('ERROR: Nebolo zadane ziadne cislo')
    #         num_of_players = int(num_of_players)
    #         if not 1 <= num_of_players <= 4:
    #             raise ValueError('ERROR: Napis cele cislo (1/2/3/4)')
    #         break
    #     except ValueError as error:
    #         print(repr(error.args[0]))
    # all_players = all_players[:num_of_players]
    # print(f'Hraci: {", ".join(player.name for player in all_players)}')
    # print('-'*45)
    num_of_players = 2

    # urcit velkost hracej plochy
    # print('Zvolte si velkost hracej plochy (neparne cislo, vacsie/rovne ako 5)')
    # while True:
    #     try:
    #         size_of_board = input()
    #         if size_of_board == '':
    #             raise ValueError('ERROR: Nebolo zadane nic')
    #         size_of_board = int(size_of_board)
    #         if not isinstance(size_of_board, int):
    #             raise ValueError(f"ERROR: Vstup ma byt typu integer (bolo zadane {type(size_of_board)})")
    #         elif size_of_board < 5:
    #             raise ValueError(f"ERROR: Vstup ma byt vacsi ako 5 (bolo zadane {size_of_board})")
    #         elif size_of_board % 2 == 0:
    #             raise ValueError(f"ERROR: Vstup ma byt neparne cislo (bolo zadane {size_of_board})")
    #         else:
    #             break
    #     except ValueError as error:
    #         print(repr(error.args[0]))
    # print(f'Hracia plocha: {size_of_board}x{size_of_board}')
    size_of_board = 11

    #zadeklarovat basic global variables
    DLZKA_DOMCEKA = size_of_board//2-1
    MATRIX_STRED = size_of_board//2+1

    # create players
    player_A = Player('A')
    player_B = Player('B')
    player_C = Player('C')
    player_D = Player('D')
    all_players = [player_A, player_B, player_C, player_D]

    #create board
    board = Board()

    # DLZKA_DOMCEKA =

# gensachovnicu(n)
# tlacsachovnicu()
#
