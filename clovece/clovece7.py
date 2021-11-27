from random import randint


AUTOMATIC = True  # TODO fix that
class Board:
    def __init__(self):
        self.winner = None
        self.n = size_of_board
        self.empty = '- '
        # self.array = {i:f'{self.empty}' for i in range((self.n-1)*4)}
        self.array = [f'{self.empty}' for _ in range((self.n-1)*4)]
        self.matrix = []
        self.gen_board()

    def gen_board(self):
        self.matrix = [["  "] + [str(i)[-1]+' ' if i < 10 else str(i)[-2:] for i in range(self.n)]] + \
                      [[' ' + str(i)[-1] if i < 10 else str(i)[-2:]] +
                       ["  " for _ in range(self.n)] for i in range(self.n)]  # basic matrix

        s = MATRIX_STRED  # middle of matrix

        self.matrix[s][s] = "XX"

        self.matrix[1][s+2] = '↓ '
        self.matrix[-1][s-2] = ' ↑'
        self.matrix[s-2][1] = '→ '
        self.matrix[s+2][-1] = '← '

    def update_board(self):
        s, d = MATRIX_STRED, home_length
        array, n, matrix = list(self.array), self.n - 1, self.matrix

        # update matrix by array values
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

        # update matrix's houses by players home values
        for i in range(d):
            matrix[s-i-1][s] = player_A.home[d-1-i]
            matrix[s+i+1][s] = player_C.home[d-1-i]
        matrix[s][s+1:s+1+d] = player_B.home[::-1]
        matrix[s][s-d:s] = player_D.home

    def print_board(self):
        self.update_board()
        for row in self.matrix:
            print(' '.join(row))
        print_line(Purple)


class Player:
    def __init__(self, name):
        self.home = ['DD' for _ in range(home_length)]
        self.name = name
        self.array = []
        self.pieces = {f'{self.name}{i+1}' for i in range(home_length)}
        self.movable = []
        self.not_movable = []
        self.empty_home = f'{self.name}-'
        self.starting_point = None
        self.define_starting_point()

    def define_starting_point(self):
        if self.name == 'A':
            self.starting_point = 0
        elif self.name == 'B':
            self.starting_point = size_of_board-1
        elif self.name == 'C':
            self.starting_point = (size_of_board-1)*2
        else:
            self.starting_point = (size_of_board-1)*2+size_of_board-1

    def check_winner(self):
        if sorted(self.home) == sorted(self.pieces):
            board.winner = self.name
            print_line(Yellow)
            print(f'WINNER IS PLAYER {Yellow+self.name+White}')
            print_line(Yellow)
            quit()

    def export_array(self):
        self.home = self.array[-home_length:]
        self.array = self.array[-self.starting_point-home_length:-home_length] + self.array[:-self.starting_point-home_length]
        board.array = self.array
        board.print_board()
        self.check_winner()

    def move(self):
        self.array = board.array[self.starting_point:] + board.array[:self.starting_point] + self.home
        self.not_movable = list(filter(lambda x: x not in self.array, self.pieces))

        if self.name not in ''.join(self.array).replace(f'{self.name}-', '- '):
            three_dice_rolls = randint(1, 6), randint(1, 6), randint(1, 6)
            print(f"Tri hody hraca {Green+self.name+White}:", ', '.join(map(str, three_dice_rolls)), '\n')
            if 6 in three_dice_rolls:
                self.array[0] = sorted(self.not_movable)[0]
                self.export_array()
                self.move()
            else:
                print(f'Na rade bol hrac {self.name} a nehodil cislo 6tku\n')
            return None

        dice_roll = randint(1, 6)

        self.movable = [p for p in self.pieces if
                        p in self.array
                        and self.array.index(p) + dice_roll < len(board.array)+home_length
                        and self.array[self.array.index(p) + dice_roll] not in list(filter(lambda x: x in self.home, self.pieces))]

        if dice_roll == 6 and self.name not in self.array[0]:
            self.movable += self.not_movable

        print(f'Na rade je hrac {self.name} a hodil cislo {Green + str(dice_roll) + White}\n')

        if len(self.movable) == 0:
            print(f"Hod kockou hraca bol {Green + self.name + White}: {dice_roll} a nemal sa s cim pohnut\n")
            return  # close player turn, cuz of nothing to move

        piece = sorted(self.movable)[0]  # only 1 piece we can move
        while len(self.movable) > 1:
            if not AUTOMATIC:
                piece = input(f"{sorted(self.movable)}"+'\n').upper()  # TODO: nastavenie automatickeho posuvana
            if piece in self.movable:
                break
            print('Zly input/s tymto panacikom nejde pohnut.')

        if piece not in self.array:
            self.array[0] = piece
        else:
            position = self.array.index(piece)
            self.array[position] = board.empty if position < len(self.array) - home_length else self.empty_home
            self.array[position+dice_roll] = piece
        self.export_array()
        if dice_roll == 6:
            self.move()

def pravidla_hry():
    print('-'*15+' PRAVIDLA HRY '+'-'*16)
    rules = [
        "Ak nema hrac ziadneho panacika na hracej ploche, hadze 3x alebo pokial nehodi 6tku",
        "Ak hrac stupi na panacika ineho hraca (alebo aj na svojho), vybije ho a teda panacik ineho hraca (alebo seba sameho) sa vrati do stajne",
        "Kazdy hrac ma na zaciatku rovnaky pocet panacikov v stajni ako je pocet domcekov"
        "Vitazom za stava hrac, kt. prvy dostane vsetky svoje pieces do domceka",
        "Ak hrac hodi 6tku, ma pravo na dalsi hod",
    ]
    for i, text in enumerate(rules):
        print(f"{i+1}. pravidlo - {text}")


def print_line(color):
    print(Strikethrough_on+color+' '*65+Strikethrough_off+White)


White = '\033[0m'  # normal
Red = '\033[31m'
Green = '\033[32m'
Yellow = '\033[33m'
Purple = '\033[35m'
Strikethrough_on = '\033[9m'
Strikethrough_off = '\033[29m'
# source http://pueblo.sourceforge.net/doc/manual/ansi_color_codes.html
# ANSI colors
# \033 - ESC


if __name__ == '__main__':
    print('Vitaj')
    pravidla_hry()
    print_line(Purple)
    print()

    # urcit pocet hracov
    print('Zvolte si pocet hracov od 1 do 4')
    while True:
        try:
            num_of_players = input()
            if num_of_players == '' or not num_of_players.isnumeric():
                raise ValueError('ERROR: Nebolo zadane cislo od 1 do 4')
            num_of_players = int(num_of_players)
            if not 1 <= num_of_players <= 4:
                raise ValueError('ERROR: Napis cele cislo (1/2/3/4)')
            break
        except ValueError as error:
            print(Red+f'{error.args[0]}'+White)
    # num_of_players = 4

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
            print(Red+f'{error.args[0]}'+White)

    # size_of_board = 11

    # zadeklarovat basic global variables
    home_length = size_of_board//2-1
    MATRIX_STRED = size_of_board//2+1

    # create board
    board = Board()

    # create players
    player_A = Player('A')
    player_B = Player('B')
    player_C = Player('C')
    player_D = Player('D')

    all_players = [player_A, player_B, player_C, player_D]
    all_players = all_players[:num_of_players]

    for player in all_players:
        player.home = [f'{player.name}-' for i in range(home_length)]

    print(f'Hraci: {", ".join(player.name for player in all_players)}')
    print_line(Purple)
    print(f'Hracia plocha: {size_of_board}x{size_of_board}')
    print_line(Purple)

    board.print_board()

    while board.winner is None:
        for player in all_players:
            player.move()