import random

money = 0
for _ in range(1000):
    money -= 9.2
    money += random.choice([16.68, 8.65, 8.9])
    print(f'{money:.2f}$')
