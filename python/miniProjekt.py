from turtle import *

pensize(2)
speed(0)
# najlepsie urobit 3 funkcie - lupen, stonka, listy => zabalit to do fun kvet() s parametrami
# odporucane velkosti
# w = <1, 7>
# l = <5, 20>
# k = <5, 35>

def draw_list(w, l, k): #w-width listu, l-length listu, k=pocet otoceni pri robeni obluku
    for _ in range(2):
        for _ in range(k):
            fd(l)
            left(w)
        left(180-k*w)
# draw_list(3, 10, 20)

def draw_top(n, w, l, k): #n-pocet listov; w,l - paremetre listu
    for _ in range(n):
        draw_list(w, l, k)
        left(360//n)
# draw_top(12, 3, 6)

def draw_stopka(w, l, k):
    left(180+90-(k-1)*w/2) #pouzil som vypocet uhla v pravidelnych n-uholnikov, konretne vonkajsi uhol
    for _ in range(k):
        fd(l)
        left(w)
    setheading(0)
# draw_stopka(5, 15, 20)

def draw_bottom(angle, w, l, k):
    left(angle-(k-1)*w/2)
    draw_list(w, l, k)
    left(180-2*angle)
    draw_list(w, l, k)
# draw_bottom(30, 7, 15, 20)

def kvet(T, S, B):
    draw_top(*T)
    draw_stopka(*S)
    draw_bottom(*B)

kvet([7, 4, 10, 20], [5, 25, 20], [30, 3, 15, 20])


exitonclick()