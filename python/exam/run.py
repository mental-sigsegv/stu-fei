Def_f(n):
_if n==0:
__return 0
_else:
__if n%2==1:
_rec=f(n-1)
_Return rec
__if n%2==0:
_rec=f(n-2)
_Return rec+n
a=f(7)
Print(a)