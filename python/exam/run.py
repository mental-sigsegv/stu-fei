DEF F(n):
____IF n<1:
________PRINT('Start!', end=' ')
____ELSE:
________PRINT(n, end=' ')
________F(n-1)
F(5)