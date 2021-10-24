for p in range(-20, 20):
    x1, x2, x3, x4 = [-1, -p, 2+p, p]
    # print(x1, x2, x3, x4)
    print(p)
    print(
        2*x1 + 5*x2 + 4*x3 + x4   == 6,
        3*x1 + 7*x2 + 6*x3 + x4   == 9,
        3*x1 + 7*x2 + 5*x3 + 2*x4 == 7,
        1*x1 + 1*x2 - 1*x3 + 2*x4 == -3
    )

