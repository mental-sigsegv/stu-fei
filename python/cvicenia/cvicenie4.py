# Uloha 10
def foo(n):
    if n < 2:
        return None
    return sorted([int(input()) for num in range(n)])[-2]
print(foo(5))

def foo(n):
    if n < 2:
        return None
    l = []
    for num in range(n):
        l.append(int(input()))
    return sorted(l)[-2]
print(foo(5))
# print(sorted(list(map(int, input().split())))[-2])


# Uloha 13
def isprime(n):
    if n == 2:
        return True
    if n%2 == 0:
        return False
    for i in range(3, int(n**0.5)+1, 2):
        if n%i == 0:
            return False
    return True

def prvocisla(r, l=[]):
    for num in range(2, r+1):
        if isprime(num):
            l.append(num)
    return l

# print(len(prvocisla(10**6)))
# print(prvocisla(50))

# Uloha 14
def pohyb_veze(x1, y1, x2, y2):
    if x1 == x2 or y1 == y2:
        return True
    return False
# print(pohyb_veze(1, 6, 2, 6))

# Uloha 15
def rovnaka_farba(x1, y1, x2, y2):
    if (x1+y1)%2 == (x2+y2)%2:
        return True
    return False
# print(rovnaka_farba(4, 3, 7, 5))

# Uloha 16
def pohyb_krala(x1, y1, x2, y2):
    if abs(x1-x2) <= 1 and abs(y1-y2) <= 1:
        return True
    return False
# print(pohyb_krala(5, 4, 4, 4))

# Uloha 17
def pohyb_strelca(x1, y1, x2, y2):
    if abs(x1-x2) == abs(y1-y2):
        return True
    return False
# print(pohyb_strelca(4, 4, 4, 5))

# Uloha 18
def pohyb_damy(x1, y1, x2, y2):
    if pohyb_strelca(x1, y1, x2, y2) and pohyb_veze(x1, y1, x2, y2):
        return True
    return False
# print(pohyb_damy(5, 5, 1, 2))

# Uloha 19
def pohyb_jazdca(x1, y1, x2, y2):
    if (abs(x1-x2) == 1 and abs(y1-y2) == 2) or (abs(x1-x2) == 2 and abs(y1-y2) == 1):
        return True
    return False
# print(pohyb_jazdca(5, 2, 4, 4))