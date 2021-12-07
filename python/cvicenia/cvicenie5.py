from functools import cache

@cache
def fibonaci(n):
    ...
    pass


def tower(n):
    c = 0
    if n == 1:
        return 1
    else:
        c += 2*tower(n-1)
        c += 1
    return c


k = 4
print(tower(k))
# print(2**k-1)


