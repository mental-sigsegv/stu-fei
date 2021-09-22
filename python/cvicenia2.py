from turtle import *

pensize(2)
speed(8)

def schody(n, a):
    for _ in range(4):
        for _ in range(n-1):
            fd(a)
            left(90)
            fd(a)
            right(90)
        fd(a)
        right(90)
# schody(6, 50)

def uholnik(n, a):
    for _ in range(n):
        angle = 360/n
        fd(a)
        left(angle)
# uholnik(5, 50)

def obr_3():
    for _ in range(10):
        uholnik(5, 100)
        left(36)

def obr_4():
    for _ in range(12):
        uholnik(12, 100)
        left(30)
# obr_4()


def obr_5(n, a):
    angle = 0
    fd(a)
    left(90)
    fd(a)
    for _ in range(n):
        d = distance(0, 0)
        print(f'{d:.2f}')
        # print(towards(0, 0))
        angle = towards(0, 0)-180
        home()
        left(angle)
        fd(d)
        left(90)
        fd(a)

speed(4)
# obr_5(4, 100)
obr_5(10, 70)

exitonclick()