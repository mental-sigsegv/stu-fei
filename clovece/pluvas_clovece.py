import random


class Pole:
	def __init__(self, *args, **kwargs):
		self.rozmer = args[0]
		self.pole = [[Policko(x, y) for y in range(self.rozmer+1)] for x in range(self.rozmer+1)]  # inicializuje prazdny 2d list s prazdnymi polickami

	def print_pole(self):
		#vypise cele pole po riadku
		for riadok in self.pole:
			for policko in riadok:
				#ak na policku je postavicka, vypise tu, ktora tam prisla posledna
				print(policko.hodnota, end=" ") if not policko.postavicka else print(policko.postavicka[-1].hodnota, end = " ")
			print()
		print()

	def init_pole(self):
		#inicializuje pole a pre kazde policko zavola funkciu assign, ktora priradi danemu policku urcitu hodnotu
		for riadok in self.pole:
			for policko in riadok:
				policko.assign(self.rozmer)

	def init_postavicka(self, postavicka):
		#inicializuje postavicku na hracie pole, funkcia sa vola pri vytvoreni novej postavicky a jej umiestnenie na startovacie policko
		for riadok in self.pole:
			for policko in riadok:
				if postavicka.policko == policko:
					policko.postavicka.append(postavicka)

	def delete_postavicka(self, postavicka):
		#vymaze postavicku z hracieho pola
		for riadok in self.pole:
			for policko in riadok:
				if postavicka.policko == policko:
					policko.postavicka.remove(postavicka)

	def move_postavicka(self, postavicka, user, n = 1):
		#pohne s postavickou "postavicka" nkrat 

		#skontroluje ci postavicka nie je pred domom a caka na hod do domceka
		if not postavicka.atdoorstep:
			#ak nie je pred domom, hybe sa po poli
			self.move_on_board(postavicka, n)
		else:
			#ak je, hybe sa do domceka
			self.move_to_home(postavicka, user, n)

	def move_on_board(self, postavicka, n):
		polovica = (self.rozmer + 1)/2
		for i in range(n):
			a_policko = postavicka.policko #aktualne policko
			#get all neighbours in radius 1
			policka = self.get_neighbours(a_policko)

			for policko in policka:
				n_miesto = False
				#ak najde pri sebe policko s hodnotu "*" a ktore nie je predosle policko, pohne sa na neho
				if policko.hodnota == '*'  and policko is not postavicka.predosle_policko:
					if postavicka.predosle_policko:
						n_miesto = True
					else: 
						#toto sa zavola ak je to cersta postavicka a nema ziadne predosle policko, musime teda skontrolovat aby to policko nebolo v polovici
						#kedze startovacie policko je vedla policok ktore su "v stredoch" ramien
						if policko.miesto[0] != polovica and policko.miesto[1] != polovica:
							n_miesto = True
					#ak po cykloch je premenna True, tak sa panacik pohne na 
					if n_miesto:
						self.change_pos(postavicka, a_policko, policko)
						break

		if len(postavicka.policko.postavicka)>1:
			#ak po dokonceni pohybu je na aktualnom policku viac ako jedna postavicka, skontroluje ci ta postavicka je ineho usera
			#ak ano, nastavi jej hodnotu deleted True, kedy pri dalsom turne toho usera sa vymaze
			for panacik in postavicka.policko.postavicka:
				if panacik != postavicka and panacik.hodnota != postavicka.hodnota:
					panacik.deleted = True

		if postavicka.policko == postavicka.home:
			#ake po skonceni pohybu je postavicka na urcenom policku odkial moze ist do domceka, tak nastavi hodnotu True
			postavicka.atdoorstep = True

	def move_to_home(self, postavicka, user, n):
		starting_policko = postavicka.policko
		starting_predosle_policko = postavicka.predosle_policko
		if n <= (self.rozmer - 3) / 2:
			for i in range(n):
				a_policko = postavicka.policko #aktualne policko
				#get all neighbours in radius 1
				foo = a_policko if i!=0 else postavicka.predosle_policko #ziskaj policko pre predosle policko, aby sme nasli "D" policko
				policka = self.get_neighbours(foo)
				#pohne sa nkrat na vedlajsie policko "D"
				for policko in policka:
					if policko.hodnota == "D" and policko is not postavicka.predosle_policko:
						self.change_pos(postavicka, a_policko, policko)
						break
			#ak po skonceni pohybu je aktualne policko uz "occupied" inou postavickou tak sa vrati na zaciatok, pre usera to vyzera ako keby sa pohyb ani nestal
			if len(policko.postavicka) > 1:
				self.change_pos(postavicka, a_policko = policko, policko = starting_policko, restart = starting_predosle_policko)
			else:
				user.panaciky_domcek.append(postavicka)
				user.panaciky_board.remove(postavicka)	

	def change_pos(self, postavicka, a_policko, policko, restart = False):
		#vymeni postavicke policko a tym padom vymaze z policka postavicku a prida k druhemu policku
		#ak je restart True, tak predosle policko je zaciatocne predosle policko -> pouzivane pri restarte pri pohybe do domceka
		postavicka.policko = policko
		postavicka.predosle_policko = a_policko if not restart else restart
		policko.postavicka.append(postavicka)
		a_policko.postavicka.remove(postavicka) 

	def get_neighbours(self, a_policko):
		#ziska vsetkych susedov pri aktualnom policku
		#najskor zoberie aktualny stlpec a aktualny riadok a z neho zoberie tie, ktorych rozdiel je presne 1
		#tymto sa zabrani list index erroru
		policka = []
		for policko in [ self.pole[x][a_policko.miesto[1]] for x in range( self.rozmer + 1)] + self.pole[ a_policko.miesto[0] ]:
			if abs(a_policko.miesto[0] - policko.miesto[0]) + abs(a_policko.miesto[1] - policko.miesto[1]) == 1:
				policka.append(policko)
		return policka


class Policko:
	def __init__(self, *args, **kwargs):
		self.miesto = [args[0], args[1]]
		self.hodnota = " "
		self.postavicka = []

	def assign(self, n):
		#priradi policku hodnotu podla umiestenia v poli
		_n = n+1 #dlzka pola aj s ocislovanim

		#najskor priradi ocislovanie ak patri do urciteho riadku alebo stlpca
		#ak nepatri tak vyskusa ci do stredovych riadkov a stlpcov a ich susedov a priradi im hodnotu hracieho policka "*"
		if self.miesto[0] == 0:
			self.hodnota = (self.miesto[1]-1)%10 if self.miesto[1]-1 != -1 else " "
		elif self.miesto[1] == 0:
			self.hodnota = (self.miesto[0]-1)%10 if self.miesto[0]-1 != -1 else " "
		elif self.miesto[1] in [_n/2, _n/2+1, _n/2-1] or self.miesto[0] in [_n/2, _n/2+1, _n/2-1] :
			self.hodnota = "*"

		#zatial mame len hodnoty hracieho policka, tak priradime hodnotu "D" pre riadok v stredu a stlpec v strede
		#davame pozor aby sme to nepriradili tam, kde je ocislovanie
		if self.miesto[0] == _n/2 and self.miesto[1] not in [0, 1, n]:
			self.hodnota = "D"
		elif self.miesto[1] == _n/2 and self.miesto[0] not in [0, 1, n]:
			self.hodnota = "D"

		#hodnota v strede bude mat najskor D, tak musime pouzit osobitne if a priradime hodnotu "X"
		if self.miesto[0] == _n/2 and self.miesto[1] == _n/2:
			self.hodnota = "X"


class Postavicka:
	def __init__(self, *args, **kwargs):
		self.policko = args[0]
		self.hodnota = args[1]
		self.predosle_policko = None
		self.home = args[0]
		self.atdoorstep = False
		self.deleted = False


class User:
	def __init__(self, *args, **kwargs):
		self.home = args[0]
		self.domcek = args[0] #legacy, na zaciatku bol self.home a self.domcek ine 
		self.panaciky_pocet = args[1]
		self.oznacenie = args[2]
		self.panaciky_board = []
		self.panaciky_domcek = []

	def turn(self, pole):
		#zavola sa kazdy turn
		hod = random.randint(1, 6)

		#pred kazdym turnom skontroluje, ci niktory panacik nebol vyhodeny
		for panacik in self.panaciky_board:
			if panacik.deleted:
				#ak bol tak ho vymaze z vlastneho zoznamu panacikov a pripocita +1 k poctu nevyuzitich
				self.panaciky_board.remove(panacik)
				self.panaciky_pocet += 1
				#vymazeme ju aj z pola
				pole.delete_postavicka(panacik)
		#vypise aktualny stav nevyuzitich panacikov a aktualny hod
		self.print_stav()
		print_hod(hod)

		#ak bol hod 6 a pocet nevyuzitich panacikov je vacsi ako 0 tak vyberie jedneho panacika na hracie pole
		if hod == 6 and self.panaciky_pocet>0:
			pole.init_postavicka(self.init_panacik())
			#ak si vyberie noveho panacika, ide znova
			hod = random.randint(1, 6) 
		if self.panaciky_board: #ak ma este nejakych panacikov tak vyberie nahodneho panacika s ktorym sa pohne
			postavicka = random.choice(self.panaciky_board)
			pole.move_postavicka(postavicka, self, hod)

		#vykreslime pole po zmenach	
		pole.print_pole()

	def init_panacik(self):
		#Vytvori novu postavicku a odpocita z poctu nevyuzitich

		postavicka = Postavicka(self.home, self.oznacenie, self.domcek)
		self.panaciky_board.append(postavicka)
		self.panaciky_pocet -= 1
		#returne vytvorenu postavicku, aby ju mohlo inicializovat aj pole
		return postavicka

	def print_stav(self):
		print(f'{self.oznacenie}: {int(self.panaciky_pocet)}')

def print_hod(n):
	print(f'Hod: {n}')

if __name__ == "__main__":
	while True: #while loop a try aby sme sa mali len neparne n cislo a vyhli sa zlemu inputu
		try:
			n = int(input("Velkost pola? "))
			if n%2==0:
				raise Exception("Parne cislo")
			else:
				break
		except ValueError:
			print("Zadajte platne neparne cislo")
		except Exception as e:
			print(f"Chyba {e}, prosim zadajte platne neparne cislo")

	#inicializuje objekt pole s n velkostou
	pole = Pole(n)
	#priradi kazdemu policku v poli nejaku hodnotu
	pole.init_pole()
	#vypise pole po inicializovani
	pole.print_pole()

	#inicializuje oboch userov a da ich do jedneho listu pre lepsie pracovanie s uzivatelmi
	userA = User(pole.pole[1][(n+1)//2+1], (n-3)/2, "A")
	userB = User(pole.pole[n][(n+1)//2-1], (n-3)/2, "B")
	users = [userA, userB]
	
	#vyuzita osobitna premenna, pretoze break by nefungoval pre while True loop nakolko mame dva cykly
	running = True
	#game loop
	while running:
		for user in users:
			#pre kazdeho usera urobi turn a ak po turne nema ziadnych panacikov tak dany user vyhrava a game loop sa zastavi
			user.turn(pole)
			if user.panaciky_pocet == 0 and not user.panaciky_board:
				print(f'{user.oznacenie} wins!')	
				running = False
				break

