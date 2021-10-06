from turtle import *

pensize(2)
speed(0)
# najlepsie urobit 3 funkcie - lupen, stonka, listy => zabalit to do fun kvet() s parametrami
# odporucane velkosti
# w = <1, 10>
# l = <10, 20>
# k = <5, 35>
k = 10 # koeficient kreslenia polkruhu
def draw_polkruh(w, l):
    for _ in range(k):
        fd(l)
        left(w)
# draw_polkruh(8, 12)

def draw_list(w, l): # w-width listu, l-length listu
    for _ in range(2):
        draw_polkruh(w, l)
        left(180-k*w)
# draw_list(10, 20)

def draw_top(n, w, l): #n-pocet listov; w-width listu, l-length listu
    for _ in range(n):
        draw_list(w, l)
        left(360//n)
# draw_top(6, 10, 20)

def draw_stopka(w, l):
    left(180+90-(k-1)*w/2) #pouzil som vypocet uhla v pravidelnych n-uholnikov, konretne vonkajsi uhol
    draw_polkruh(w, l)
    setheading(0)
# draw_stopka(12, 30)

def draw_bottom(angle, w, l):
    left(angle-(k-1)*w/2)
    draw_list(w, l)
    left(180-2*angle)
    draw_list(w, l)
# draw_bottom(55, 6, 15)

def kvet(T, S, B):
    draw_top(*T)
    draw_stopka(*S)
    draw_bottom(*B)

def kvety():
        penup(); back(400); left(90); fd(150); pendown(); right(90)
        kvet([7, 6, 14], [8, 40], [30, 4, 10]) # Prvy kvet
        # return None

        penup(); home(); left(90); fd(150); pendown(); right(90)
        kvet([10, 8, 16], [4, 55], [70, 1, 22]) # Druhy kvet

        penup(); home(); fd(400); left(90); fd(150); pendown(); right(90)
        kvet([10, 2, 12], [1, 30], [45, 7, 20]) # Treti kvet
# kvety()

kvet([0, 0, 0], [0, 0], [0, 0, 0])

exitonclick()