from random import randint


class Board:
    def __init__(self):
        self.winner = None
        self.n = size_of_board
        self.empty = '- '  # defines empty slot on movable path
        self.array = [f'{self.empty}' for _ in range((self.n-1)*4)]  # array of length of movable path
        self.matrix = []  # 2d matrix that is printed to the console
        self.gen_board()

    # define basic look of board into 2d metrix
    def gen_board(self):
        self.matrix = [["  "] + [str(i)[-1]+' ' if i < 10 else str(i)[-2:] for i in range(self.n)]] + \
                      [[' ' + str(i)[-1] if i < 10 else str(i)[-2:]] +
                       ["  " for _ in range(self.n)] for i in range(self.n)]  # basic matrix

        s = MATRIX_STRED  # middle of matrix

        # define fancy look (XX, arrows)
        self.matrix[s][s] = "XX"

        self.matrix[1][s+2] = '↓ '
        self.matrix[-1][s-2] = ' ↑'
        self.matrix[s-2][1] = '→ '
        self.matrix[s+2][-1] = '← '

    # update of board
    def update_board(self):
        s, d = MATRIX_STRED, home_length
        array, n, matrix = list(self.array), self.n - 1, self.matrix

        # update matrix by array values (movable path), PS: it's messy, but it works, don't touch it ;)
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

        # update matrix's houses values by players home values
        for i in range(d):
            matrix[s-i-1][s] = player_A.home[d-1-i]
            matrix[s+i+1][s] = player_C.home[d-1-i]
        matrix[s][s+1:s+1+d] = player_B.home[::-1]
        matrix[s][s-d:s] = player_D.home

    # function for printing board into console
    def print_board(self):
        self.update_board()  # updating board before printing
        for row in self.matrix:  # printing rows in matrix
            print(' '.join(row))
        print_line(Purple)  # add fancy line to divide text into parts in console


class Player:
    def __init__(self, name):
        self.home = ['DD' for _ in range(home_length)]
        self.name = name
        self.array, self.movable, self.not_movable = [], [], []
        self.pieces = {f'{self.name}{i+1}' for i in range(home_length)}
        self.empty_home = f'{self.name}-'
        self.starting_point = None
        self.define_starting_point()

    # define starting points of every player
    def define_starting_point(self):
        if self.name == 'A':
            self.starting_point = 0
        elif self.name == 'B':
            self.starting_point = size_of_board-1
        elif self.name == 'C':
            self.starting_point = (size_of_board-1)*2
        else:
            self.starting_point = (size_of_board-1)*2+size_of_board-1

    # define winner, if winner exists, exit program
    def check_winner(self):
        if sorted(self.home) == sorted(self.pieces):
            board.winner = self.name
            print_line(Yellow)
            print(f'WINNER IS PLAYER {Yellow+self.name+White}')
            print_line(Yellow)
            exit()

    # export values of player.array into matrix, print board and check if we got a winner
    def export_array(self):
        self.home = self.array[-home_length:]
        self.array = self.array[-self.starting_point-home_length:-home_length] + self.array[:-self.starting_point-home_length]
        board.array = self.array
        board.print_board()
        self.check_winner()

    # move function of player
    def move(self):
        self.array = board.array[self.starting_point:] + board.array[:self.starting_point] + self.home
        self.not_movable = list(filter(lambda x: x not in self.array, self.pieces))

        # throw a dice three times if none piece on board
        if self.name not in ''.join(self.array).replace(f'{self.name}-', '- '):
            three_dice_rolls = randint(1, 6), randint(1, 6), randint(1, 6)
            print(f"Tri hody hraca {Green+self.name+White}:", ', '.join(map(str, three_dice_rolls)), '\n')
            if 6 in three_dice_rolls:  # if 6 in throws add piece at player's starting_point
                self.array[0] = sorted(self.not_movable)[0]
                self.export_array()
                self.move()
            else:
                print(f'Na rade bol hrac {self.name} ale nehodil cislo 6')
                print_line(Purple)
            return None

        dice_roll = randint(1, 6)

        # define pieces that I can move with based on position and dice_roll
        self.movable = [p for p in self.pieces if
                        p in self.array
                        and self.array.index(p) + dice_roll < len(board.array)+home_length
                        and self.array[self.array.index(p) + dice_roll] not in list(filter(lambda x: x in self.home, self.pieces))]

        # add not_movable pieces (not on board) to movable (cuz I can add them to board) ->
        # -> if dice_roll = 6 and starting_point of player is empty
        if dice_roll == 6 and self.name not in self.array[0]:
            self.movable += self.not_movable

        print(f'Na rade je hrac {self.name} a hodil cislo {Green + str(dice_roll) + White}\n')

        # close player turn, cuz of nothing to move with
        if len(self.movable) == 0:
            print(f"Hod kockou hraca bol {Green + self.name + White}: {dice_roll} a nemal sa s cim pohnut")
            print_line(Purple)
            return

        piece = sorted(self.movable)[0]  # 1. piece we can move with - usefull when automatic is ON
        while len(self.movable) > 1:
            if not AUTOMATIC:
                piece = input(f"{sorted(self.movable)}"+'\n').upper()  # ask for piece to move with
            if piece in self.movable:
                break
            print('Zly input alebo s tymto panacikom nejde pohnut.')

        # if pice is not on board/home and it's in moveable -> we want new piece
        if piece not in self.array:
            self.array[0] = piece
        else:
            # get position of piece, clear that position and 'move' piece to another position (last position+dice_roll)
            position = self.array.index(piece)
            self.array[position] = board.empty if position < len(self.array) - home_length else self.empty_home
            self.array[position+dice_roll] = piece
        self.export_array()
        if dice_roll == 6:
            self.move()


# rules
def rules():
    print(Yellow + '-'*15+' PRAVIDLA HRY '+'-'*16)
    rules = [
        "Hráči majú fixnuté domčeky a štartovacie pozície bez ohľadu na počet hráčov.",
        "Pohyb panáčika je v protismere hodinových ručičiek.",
        "Každý hráč má rovnaký počet panáčikov ako je počet jeho domčekov.",
        "Ak nemá hráč žiadneho panáčika na hracej ploche ani v domčeku, hádže kockou 3-krát.",
        "Ak hráč hodí 6-tku, ide znova.",
        "Ak hráč stúpi na panáčika mimo domčeka, vybije ho.",
        "Panáčik, ktorý je v domčeku sa nedá vybiť.",
        "Víťazom sa stáva hráč, ktorý prvý dostane všetkých svojich panáčikov do domčeka."
        "Ak je aktivované hranie (nie automatické), tak hra vyzve hráča aby na vstup zadal panáčika, s ktorým sa chce hráč pohnúť (ak je na výber z viacerých panáčikov)"
    ]
    # print rules with order number
    for i, text in enumerate(rules):
        print(f"{i+1}. {text}")
    print(White)
    input('Stlač ENTER ak chceš pokračovať ďalej.')  # time to let player read rules


# function to print line with defined color
def print_line(color):
    print(Strikethrough_on+color+f'{" " if COLORS else "-"}'*65+Strikethrough_off+White)


def info():
    print(f'\nInformation\n'
          f'Autor: {"Martin Klacik"}\n'
          f'Description: {"STU FEI projekt"}\n'
          f'Python version: {3.9}\n'
          f'Libraries: [random]\n'
          f'Developed in: PyCharm (farby sa v default .py IDLE nemusia zobraziť, potom doporučujem farby vypnúť)\n')


if __name__ == '__main__':
    AUTOMATIC = False  # setting for automatic play
    COLORS = False  # setting for using ANSI colors (no need of external library)

    info()
    # define if the game will use ANSI colors or not by user's input
    while True:
        answer = input('Chcete použiť farby (yes/no)?\n')
        if answer.lower() in ['yes', 'y', 'ano', 'áno']:
            COLORS = True
            break
        elif answer.lower() in ['no', 'n', 'nie']:
            break

    # ANSI colors - doesnt work in default python IDLE, use VScode or PyCharm instead!
    White = '\033[0m' if COLORS else ''  # default color
    Red = '\033[31m' if COLORS else ''
    Green = '\033[32m' if COLORS else ''
    Yellow = '\033[33m' if COLORS else ''
    Purple = '\033[35m' if COLORS else ''
    Strikethrough_on = '\033[9m' if COLORS else ''  # it makes line clear
    Strikethrough_off = '\033[29m' if COLORS else ''
    # source http://pueblo.sourceforge.net/doc/manual/ansi_color_codes.html

    # define if the game will be played automaticly or by the player by user's input
    while True:
        answer = input('Chcel by si si hru zahrať alebo ju dokončiť automaticky (play/auto)?\n')
        if isinstance(answer, str) and answer.lower() in ['play', 'p']:
            break
        elif isinstance(answer, str) and answer.lower() in ['auto', 'automatic', 'a']:
            AUTOMATIC = True
            break
    print_line(Purple)

    # define numbers of players by user's input
    while True:
        try:
            num_of_players = input('Zvolte si pocet hracov od 1 do 4\n')
            if not num_of_players.isnumeric() or not (1 <= int(num_of_players) <= 4):
                raise ValueError('ERROR: Nebolo zadane cislo od 1 do 4')
            num_of_players = int(num_of_players)
            break
        except ValueError as error:
            print(Red+f'{error.args[0]}'+White)

    # define size of the board by user's input
    while True:
        try:
            size_of_board = input('Zvolte si velkost hracej plochy (neparne cislo, >= 5)\n')
            if not size_of_board.isnumeric() or int(size_of_board) % 2 == 0 or not (int(size_of_board) >= 5):
                raise ValueError('ERROR: Bol zadany nevhodny vstup')
            size_of_board = int(size_of_board)
            break
        except ValueError as error:
            print(Red+f'{error.args[0]}'+White)

    print_line(Purple)
    print('\nVitaj v hre človeče nehnevaj sa\n')
    rules()

    # zadeklarovat basic global variables
    home_length = size_of_board//2-1
    MATRIX_STRED = size_of_board//2+1

    # create board
    board = Board()

    # create player objects
    player_A = Player('A')
    player_B = Player('B')
    player_C = Player('C')
    player_D = Player('D')

    # define all players that play
    all_players = [player_A, player_B, player_C, player_D]
    all_players = all_players[:num_of_players]

    # show 'active' home on board (players that dont play will have 'DD' sign as home)
    for player in all_players:
        player.home = [f'{player.name}-' for i in range(home_length)]

    # print players and board size
    print_line(Purple)
    print(f'Hráči: {", ".join(player.name for player in all_players)}')
    print(f'Hracia plocha: {size_of_board}x{size_of_board}')
    print_line(Purple)

    # defualt look of board
    print('Default board at the start of the game.\n')
    board.print_board()

    # waiting for winner of the game
    while board.winner is None:
        for player in all_players:
            player.move()
