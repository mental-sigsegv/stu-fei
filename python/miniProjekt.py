import turtle
from turtle import *


delay(0)
k = 10 # koeficient kreslenia polkruhu


def draw_polkruh(w, l, tur):
    for _ in range(k):
        tur.fd(l)
        tur.left(w)
# draw_polkruh(8, 12)

def draw_list(w, l, tur): # w-width listu, l-length listu
    for _ in range(2):
        draw_polkruh(w, l, tur)
        tur.left(180-k*w)
# draw_list(10, 20)

def draw_top(n, w, l, tur): #n-pocet listov; w-width listu, l-length listu
    for _ in range(n):
        draw_list(w, l, tur)
        tur.left(360//n)
# draw_top(6, 10, 20)

def draw_stopka(w, l, tur):
    tur.left(180+90-(k-1)*w/2) #pouzil som vypocet uhla v pravidelnych n-uholnikov, konretne vonkajsi uhol
    draw_polkruh(w, l, tur)
    tur.setheading(0)
# draw_stopka(12, 30)

def draw_bottom(angle, w, l, tur):
    tur.left(angle-(k-1)*w/2)
    draw_list(w, l, tur)
    tur.left(180-2*angle)
    draw_list(w, l, tur)
# draw_bottom(55, 6, 15)

def kvet(T, S, B, tur):
    # tur.pensize(2)
    draw_top(*T, tur)
    draw_stopka(*S, tur)
    draw_bottom(*B, tur)


def kvety(k1 = turtle.Turtle()):
        penup(); fd(1000)
        k1.penup(); k1.back(400); k1.left(90); k1.fd(150); k1.pendown(); k1.right(90)
        kvet([7, 6, 14], [8, 40], [30, 4, 10], k1) # Prvy kvet
        # return None

        k1.penup(); k1.home(); k1.left(90); k1.fd(150); k1.pendown(); k1.right(90)
        kvet([10, 8, 16], [4, 55], [70, 1, 22], k1) # Druhy kvet

        k1.penup(); k1.home(); k1.fd(400); k1.left(90); k1.fd(150); k1.pendown(); k1.right(90)
        kvet([20, 2, 12], [1, 30], [45, 7, 20], k1) # Treti kvet
kvety()

import threading
def multi_tasking():
    penup(); fd(1000)
    k1 = turtle.Turtle()
    k1.penup(); k1.back(400); k1.left(90); k1.fd(150); k1.pendown(); k1.right(90)
    k2 = turtle.Turtle()
    k2.penup(); k2.home(); k2.left(90); k2.fd(150); k2.pendown(); k2.right(90)
    k3 = turtle.Turtle()
    k3.penup(); k3.home(); k3.fd(400); k3.left(90); k3.fd(150); k3.pendown(); k3.right(90)

    p1 = threading.Thread(target=kvet, args=[[7, 6, 14], [8, 40], [30, 4, 10], k1], daemon=True)
    p1.start()
    p2 = threading.Thread(target=kvet, args=([10, 8, 16], [4, 55], [70, 1, 22], k2), daemon=True)
    p2.start()
    p3 = threading.Thread(target=kvet, args=([10, 2, 12], [1, 30], [45, 7, 20], k3), daemon=True)
    p3.start()
# multi_tasking()

mainloop()
# exitonclick()