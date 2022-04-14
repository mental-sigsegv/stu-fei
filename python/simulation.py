import random

money = 0
max_money = 0
for _ in range(1000):
    money -= 10
    money += random.choice([5, 7, 10, 12, 17])*0.95
    if money > max_money:
        max_money = money
    print(f'{money:.2f}$')
print(f'{max_money:.2f}')
