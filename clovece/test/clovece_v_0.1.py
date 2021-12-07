from random import randint

class player():
    def __init__(self, size_of_board, name):
        self.name = name
        self.size_of_board = size_of_board
        self.DLZKA_DOMCEKA = DLZKA_DOMCEKA
        self.panacikovia = {f'{self.name}{i}':None for i in range(1, self.DLZKA_DOMCEKA+1)}
        self.starting_point = 0 if self.name == 'A' else (size_of_board-1)*2

    def get_position(self):
        return self.panacikovia

class board():
    def __init__(self, size_of_board):
        self.n = size_of_board
        self.matrix = None
        self.podmienka = self.check_podmienky()
        self.array = ['*' for i in range((self.n-1)*4)]
        if self.podmienka is False:
            self.gensachovnicu()
            self.update_matrix()

    def check_podmienky(self):
        # podmienky matrixu
        if not isinstance(self.n, int):
            return f"Vstup ma byt typu integer (bolo zadane {type(self.n)})"
        elif self.n < 0:
            return f"Vstup ma byt kladne cislo (bolo zadane {self.n})"
        elif self.n % 2 == 0:
            return f"Vstup ma byt neparne cislo (bolo zadane {self.n})"
        elif self.n < 5:
            return f"Vstup ma byt vacsi ako 5 (bolo zadane {self.n})"
        return False

    def gensachovnicu(self):
        self.matrix =  [[" "] + [str(i)[-1] for i in range(self.n)]] + [[str(i)[-1]]+[" " for _ in range(self.n)] for i in range(self.n)] #zakladny matrix
        s = MATRIX_STRED  #stred matrixu

        # nastavenie domcekov na "D" a stredu na "X"
        for d in range(1, DLZKA_DOMCEKA+1):
            self.matrix[s][s+d] = "D"    #domceky na pravo od stredu
            self.matrix[s][s-d] = "D"    #domceky na lavo od stredu
            self.matrix[s+d][s] = "D"    #domceky na hore od stredu
            self.matrix[s-d][s] = "D"    #domceky na dole od stredu
        self.matrix[s][s] = "X"

    def tlacsachovnicu(self):
        if self.podmienka is not False:
            print(self.podmienka)
        else:
            for row in self.matrix:
                print(' '.join(row))
        print('-'*43)

    def update_matrix(self):
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
        return matrix

def game(n):
    global DLZKA_DOMCEKA
    global MATRIX_STRED
    global hracA
    global hracB
    global sachovnica
    DLZKA_DOMCEKA = n//2-1
    MATRIX_STRED = n//2+1
    sachovnica = board(n)
    hracA = player(n, "A")
    hracB = player(n, "B")

    hracA.panacikovia.update({'A1':hracA.starting_point})
    hracB.panacikovia.update({'B1':hracB.starting_point})

    for panacik, position in hracA.panacikovia.items():
        if position is not None:
            sachovnica.array[position] = panacik

    for panacik, position in hracB.panacikovia.items():
        if position is not None:
            sachovnica.array[position] = panacik

    sachovnica.update_matrix()
    sachovnica.tlacsachovnicu()

    hrac_A()
    hrac_B()

    # while True:
    #     panacik_name = 'A1'
    #
    #     try:
    #
    #         print('-'*43)
    #         r = randint(1, 6)
    #         print("Random integer: ", r)
    #         sachovnica.array = list(''.join(sachovnica.array).replace(panacik_name, '*'))
    #         hracA.panacikovia.update({panacik_name : hracA.panacikovia.get(panacik_name)+r})
    #         for panacik, position in hracA.panacikovia.items():
    #             if position is not None:
    #                 sachovnica.array[position] = panacik
    #         sachovnica.update_matrix()
    #         sachovnica.tlacsachovnicu()
    #     except IndexError:
    #        break

def hrac_A():
    r = randint(1, 6)
    print("Random integer: ", r)
    for panacik, position in hracA.panacikovia.items():
        if position is not None:
            sachovnica.array = ' '.join(sachovnica.array).replace(panacik, '*').split(' ')
            hracA.panacikovia.update({panacik : hracA.panacikovia.get(panacik)+r})
            for panacik, position in hracA.panacikovia.items():
                if position is not None:
                    sachovnica.array[position] = panacik
            sachovnica.update_matrix()
            sachovnica.tlacsachovnicu()


def hrac_B():
    r = randint(1, 6)
    print("Random integer: ", r)
    for panacik, position in hracB.panacikovia.items():
        if position is not None:
            sachovnica.array = ' '.join(sachovnica.array).replace(panacik, '*').split(' ')
            hracB.panacikovia.update({panacik : hracB.panacikovia.get(panacik)+r})
            for panacik, position in hracB.panacikovia.items():
                if position is not None:
                    sachovnica.array[position] = panacik
            sachovnica.update_matrix()
            sachovnica.tlacsachovnicu()

def main():
    # print('-'*43)
    game(15)
    # print('-'*43)
    # game(15)
main()
