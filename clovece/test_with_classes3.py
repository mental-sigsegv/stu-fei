class Board():
    def __init__(self):
        self.n = size_of_board
        self.matrix = []
        self.array = [str(i) for i in range((self.n-1)*4)]
        # self.array = list('*'*(self.n-1)*4)
        self.gen_board()
        self.update_board()
        self.print_board()

    def gen_board(self):
        self.matrix = [[" "] + [str(i)[-1] for i in range(self.n)]] + [[str(i)[-1]]+[" " for _ in range(self.n)] for i in range(self.n)] #zakladny matrix
        s = MATRIX_STRED  #stred matrixu

        # nastavenie domcekov na "D" a stredu na "X"
        for d in range(1, DLZKA_DOMCEKA+1):
            self.matrix[s][s+d] = "D"    #domceky na pravo od stredu
            self.matrix[s][s-d] = "D"    #domceky na lavo od stredu
            self.matrix[s+d][s] = "D" #self.hracAdomcek[d-1]    #domceky na hore od stredu
            self.matrix[s-d][s] = "D" #self.hracBdomcek[d-1]    #domceky na dole od stredu
        self.matrix[s][s] = "X"

    def update_board(self):
        array = self.array
        s = MATRIX_STRED
        d = DLZKA_DOMCEKA
        n = self.n - 1
        matrix = self.matrix

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

    def print_board(self):
        for row in self.matrix:
            print(' '.join(row))
        print('-'*45)


class Player():
    def __init__(self, name):
        self.name = name

# zadeklarovat vsetkych hracov
player_A = Player('A')
player_B = Player('B')
player_C = Player('C')
player_D = Player('D')
all_players = [player_A, player_B, player_C, player_D]

if __name__ == '__main__':
    # print('Vitaj')
    # print('-'*45)
    # print('Pravidla')
    # print('-'*45)
    # print()

    # urcit pocet hracov
    print('Zvolte si pocet hracov od 1 do 4')
    while True:
        try:
            num_of_players = input()
            if num_of_players == '':
                raise ValueError('ERROR: Nebolo zadane ziadne cislo')
            num_of_players = int(num_of_players)
            if not 1 <= num_of_players <= 4:
                raise ValueError('ERROR: Napis cele cislo (1/2/3/4)')
            break
        except ValueError as error:
            print(repr(error.args[0]))
    all_players = all_players[:num_of_players]
    print(f'Hraci: {", ".join(player.name for player in all_players)}')
    print('-'*45)

    # urcit velkost hracej plochy
    print('Zvolte si velkost hracej plochy (neparne cislo, vacsie/rovne ako 5)')
    while True:
        try:
            size_of_board = input()
            if size_of_board == '':
                raise ValueError('ERROR: Nebolo zadane nic')
            size_of_board = int(size_of_board)
            if not isinstance(size_of_board, int):
                raise ValueError(f"ERROR: Vstup ma byt typu integer (bolo zadane {type(size_of_board)})")
            elif size_of_board < 5:
                raise ValueError(f"ERROR: Vstup ma byt vacsi ako 5 (bolo zadane {size_of_board})")
            elif size_of_board % 2 == 0:
                raise ValueError(f"ERROR: Vstup ma byt neparne cislo (bolo zadane {size_of_board})")
            else:
                break
        except ValueError as error:
            print(repr(error.args[0]))
    print(f'Hracia plocha: {size_of_board}x{size_of_board}')

    #zadeklarovat basic global variables
    DLZKA_DOMCEKA = size_of_board//2-1
    MATRIX_STRED = size_of_board//2+1

    #create board
    board = Board()

    # DLZKA_DOMCEKA =

# gensachovnicu(n)
# tlacsachovnicu()
#
