# Uloha 15
def grid(n, k=4):
    for _ in range(n):
        print(('+ ' + '- '*k)*n + '+')
        for _ in range(k):
            print(('| ' + '  '*k)*n + '|')
    print(('+ ' + '- '*k)*n + '+')

grid(3)

# Uloha 15.1
# def grid_extended(x, y, k=6):
#     if x < 1 or y < 1:
#         print('Invalid num')
#         return None
#
#     for _ in range(y):
#         print(('+ ' + '- '*k)*x + '+')
#         for _ in range(k):
#             print(('| ' + '  '*k)*x + '|')
#     print(('+ ' + '- '*k)*x + '+')
#
# grid_extended(4,2)