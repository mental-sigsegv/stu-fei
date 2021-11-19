class Board():
    pass

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
    print('Vitaj')
    print('-'*45)
    print('Pravidla')
    print('-'*45)
    print()
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

    #zadeklarovat basic variables
    # DLZKA_DOMCEKA =

# gensachovnicu(n)
# tlacsachovnicu()
#
