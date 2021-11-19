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
        self.array = list('*'*(self.n-1)*4)
        self.hracAdomcek = [str(i) for i in range(DLZKA_DOMCEKA)][::-1]
        self.hracBdomcek = [str(i) for i in range(DLZKA_DOMCEKA)][::-1]
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
            self.matrix[s+d][s] = self.hracAdomcek[d-1]    #domceky na hore od stredu
            self.matrix[s-d][s] = self.hracBdomcek[d-1]    #domceky na dole od stredu
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

    def update_array(self, panacik, position):
        self.array = " ".join(self.array).replace(panacik, '*').split()
        self.array[position] = panacik
        self.update_matrix()
        self.tlacsachovnicu()

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

    sachovnica.update_matrix()
    sachovnica.tlacsachovnicu()
    #

    hrac_A()
    hrac_B()
    hrac_A()
    hrac_B()
    hrac_A()
    hrac_B()
    hrac_A()
    hrac_B()
    hrac_A()
    hrac_B()


def hrac_A():
    print('ide hrac a')
    r = randint(1, 6)
    moveable = dict(filter(lambda x: isinstance(x[1], int) and x[1]+r<=len(sachovnica.array)+DLZKA_DOMCEKA, hracA.panacikovia.items()))
    if 'A' not in ''.join(sachovnica.array):
        tri_hody = randint(1, 6), randint(1, 6), randint(1, 6)
        print(tri_hody)
        if 6 in tri_hody:
            hracA.panacikovia.update({'A1':0})
            sachovnica.update_array('A1', hracA.starting_point)
            hrac_A()

    elif r == 6 and sachovnica.array[hracA.starting_point] == '*':
        print("Random integer: ", r)
        panacik = input(f"{sorted(set(hracA.panacikovia | moveable))}"+'\n').upper()
        hracA.panacikovia.update({panacik:0})
        sachovnica.update_array(panacik, hracA.starting_point)
        hrac_A()

    elif len(moveable) == 1 and r != 6:
        print("Random integer: ", r)
        hracA.panacikovia.update({list(moveable)[0]:hracA.panacikovia.get(list(moveable)[0])+r})
        sachovnica.update_array(list(moveable)[0], moveable.get(list(moveable)[0])+r)


    elif len(moveable) > 1:
        print("Random integer: ", r)
        panacik = input(f'{sorted(set(moveable))}'+'\n').upper()
        hracA.panacikovia.update({panacik:hracA.panacikovia.get(panacik)+r})
        sachovnica.update_array(panacik, moveable.get(panacik)+r)


def hrac_B():
    print('ide hrac b')
    r = randint(1, 6)
    moveable = dict(filter(lambda x: isinstance(x[1], int) and x[1]+r<=len(sachovnica.array)+DLZKA_DOMCEKA, hracB.panacikovia.items()))
    if 'B' not in ''.join(sachovnica.array):
        tri_hody = randint(1, 6), randint(1, 6), randint(1, 6)
        print(tri_hody)
        if 6 in tri_hody:
            hracB.panacikovia.update({'B1':hracB.starting_point})
            sachovnica.update_array('B1', hracB.starting_point)
            hrac_B()

    elif r == 6 and sachovnica.array[hracB.starting_point] == '*':
        print("Random integer: ", r)
        panacik = input(f"{sorted(set(hracB.panacikovia | moveable))}"+'\n').upper()
        hracB.panacikovia.update({panacik:0})
        sachovnica.update_array(panacik, hracB.starting_point)
        hrac_B()

    elif len(moveable) == 1 and r != 6:
        print("Random integer: ", r)
        hracB.panacikovia.update({list(moveable)[0]:hracB.panacikovia.get(list(moveable)[0])+r})
        sachovnica.update_array(list(moveable)[0], moveable.get(list(moveable)[0])+r)


    elif len(moveable) > 1:
        print("Random integer: ", r)
        panacik = input(f'{sorted(set(moveable))}'+'\n').upper()
        hracB.panacikovia.update({panacik:hracB.panacikovia.get(panacik)+r})
        sachovnica.update_array(panacik, moveable.get(panacik)+r)


def main():
    # print('-'*43)
    game(15)
    # print('-'*43)
    # game(15)
main()
