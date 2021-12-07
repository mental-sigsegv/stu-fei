# 7. Bonusova
def foo():
    nums = [0]
    c = 0
    max_c = 0
    k = 0
    while True:
        i = int(input())
        if i == 0:
            return max_c
        # else:
        #     if nums[-1] == i or nums[-1] == 0:
        #         c += 1
        #         if c > max_c:
        #             max_c = c
        #     else:
        #         c = 1
        #     nums.append(i)

        else:
            if k == i or k == 0:
                c += 1
                k = i
                if c > max_c:
                    max_c = c
            else:
                k = i
                c = 1
            nums.append(i)

print(foo())