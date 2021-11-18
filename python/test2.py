import random

x = [random.randint(1, 100) for _ in range(10_000)] + [0]
print(x)