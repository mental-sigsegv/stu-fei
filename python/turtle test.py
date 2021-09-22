from turtle import *

speed(10)
pensize(2)

def stvorec(a):
    for _ in range(4):
        fd(a)
        left(90)
    exitonclick()
# stvorec(50)

def rovno_troj(a):
    for _ in range(3):
        fd(a)
        left(120)
    exitonclick()
# rovno_troj(100)

def patuholnik(a):
    for _ in range(5):
        fd(a)
        left(72)
    exitonclick()
# patuholnik(70)

def schody(a, n):
    for _ in range(4):
        for _ in range(n-1):
            fd(a)
            left(90)
            fd(a)
            right(90)
        fd(a)
        right(90)
    exitonclick()
# schody(50, 2)
# schody(30, 6)

def kosostvorec(a, angle):
    for _ in range(2):
        fd(a)
        left(angle)
        fd(a)
        left(180-angle)
    # exitonclick()

def kvet(strana):
    for _ in range(2):
        for _ in range(5):
            kosostvorec(strana, 72)
            left(72)
        left(72//2)
    right(72//2)
    fd(strana)
    left(72)
    fd(strana)
    left(72)

    for _ in range(10):
        fd(strana)
        left(36)

    exitonclick()

# kvet(70)

def uholnik(n, a):
    for _ in range(n):
        angle = 360/n
        fd(a)
        left(angle)
    # exitonclick()

def kvet2(pocet_kruhov, n ,a):
    for _ in range(pocet_kruhov):
        uholnik(n, a)
        left(360/n)
    exitonclick()
# kvet2(12, 12, 50)