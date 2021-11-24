from random import randint
from functools import reduce

# bonus pomocou reduce
max_range = 15
nums = 6

def print_interval(intervals):
    for start, end in intervals:
        print(f'{"   "*(start)}{" 0"+str(start) if start < 10 else " " + str(start)}{" =="*(end-start-1)}{" 0"+str(end) if end < 10 else " " + str(end)}')

def intervals():
    lst = []
    for _ in range(nums):
        x = randint(0, max_range)
        y = randint(x+1, max_range+1)
        lst.append((x,y))
    # lst = custom_test_list
    print(lst)
    print_interval(lst)
    lst = reduce(lambda x, y: (max(x[0], y[0]), min(x[1], y[1])), lst)
    if lst[0] >= lst[1]:
        return False
    return lst

# # print_interval([[0, i] for i in range(1, max_range+1)])

# while True:
#     interval = intervals()
#     print(interval)
#     print('\033[33m'+"-"*75+'\033[0m')
#     if interval is not False:
#         break

# bonus bez kniznice
def intervals2():
    lst = []
    for _ in range(nums):
        x = randint(0, max_range)
        y = randint(x+1, max_range+1)
        lst.append((x,y))
    # lst = custom_test_list
    print(lst)
    print_interval(lst)
    start, end = max([i[0] for i in lst]), min([i[1] for i in lst])
    if start >= end:
        return False
    return (start, end)

# while True:
#     interval2 = intervals2()
#     print(interval2)
#     print('\033[33m'+"-"*75+'\033[0m')
#     if interval2 is not False:
#         break

#test
# custom_test_list = [(7, 14), (4, 13), (9, 12), (9, 11), (2, 13), (4, 13)]
# print(intervals())
# print('\033[33m'+"-"*75+'\033[0m')
# print(intervals2())

# shortest
def intervals3(lst):
    start, end = max([i[0] for i in lst]), min([i[1] for i in lst])
    return False if end-start < 0 else (start, end)
# print(intervals3([(7, 14), (4, 13), (9, 12), (9, 11), (2, 13), (4, 13)]))