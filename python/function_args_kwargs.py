def fun(a, b, c, *args, **kwargs):
    return a, b, c, *args, *kwargs.values()

print(fun(1,2,3,4,5, d=6, f=7))