# Uloha 11, 12
def geo_rad(r, n, c=0, l=[]):
    for i in range(n):
        c += r**i
        l.append(c)
    return l
# print(geo_rad(2, 10))
# print(geo_rad(0.25, 10))

# Uloha 13
def geo_rad_bu(r, n, c=0, l=[1]):
    for i in range(n-1):
        if i == 0:
            l.append(r+1)
        else:
            c = l[-1]+(l[-1]-l[-2])*r
            l.append(c)
    return l
# print(geo_rad_bu(2,10))
# print(geo_rad_bu(0.25, 10))

# Uloha 15
def grid(n, k=2):
    for _ in range(n):
        print(('+ ' + '- '*k)*n + '+')
        for _ in range(k):
            print(('| ' + '  '*k)*n + '|')
    print(('+ ' + '- '*k)*n + '+')
grid(25)

# Uloha 15.1
def grid_extended(x, y, k=4):
    if x < 1 or y < 1:
        print('Invalid num')
        return None

    for _ in range(y):
        print(('+ ' + '- '*k)*x + '+')
        for _ in range(k):
            print(('| ' + '  '*k)*x + '|')
    print(('+ ' + '- '*k)*x + '+')
# grid_extended(12,4)