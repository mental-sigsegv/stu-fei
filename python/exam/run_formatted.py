def f(n):
    if n<1:
        print('start!', end='')
    else:
        print(n, end='')
        f(n-1)
f(5)
