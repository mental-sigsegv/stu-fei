from random import randint

# bonus pomocou reduce
max_range = 15
nums = 6

def print_interval(intervals):
    for start, end in intervals:
        print(f'{"   "*(start)}{" 0"+str(start) if start < 10 else " " + str(start)}{" =="*(end-start-1)}{" 0"+str(end) if end < 10 else " " + str(end)}')

# bonus bez kniznice
def intervals():
    lst = []
    for _ in range(nums):
        x = randint(0, max_range)
        y = randint(x+1, max_range+1)
        lst.append((x, y))
    # lst = custom_test_list
    print(lst)
    print_interval(lst)
    start, end = max([i[0] for i in lst]), min([i[1] for i in lst])
    if start >= end:
        return False
    return (start, end)

while True:
    interval = intervals()
    print(interval)
    print('\033[33m'+'\033[9m'+" "*75+'\033[0m'+'\033[29m') #ANSI color codes
    if interval is not False:
        break
