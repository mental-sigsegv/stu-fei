def f(n):
   if n==0:
      return 0
   else:
      if n%2==1:
         rec=f(n-1)
         return rec
      if n%2==0:
         rec=f(n-2)
         return rec+n
a=f(7)
print(a)
