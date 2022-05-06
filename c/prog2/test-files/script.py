import json

x = set()

with open("c/prog2/test-files/script.txt", "r") as f:
    f_data = f.read().splitlines()
    # print(f_data)

for word in f_data:
    x.add(word.strip())

# print(repr(x).replace("'", '"'))
print(len(x))