import math


def fun(x):
    return x ** 2 + 0.49 * x - 0.147


def dfun(x):
    return 2 * x + 0.49


def bisection(a, b, delta):
    a_arr, b_arr, c_aar = [], [], []
    fa = fun(a)
    signa = int(math.copysign(1, fa))
    fb = fun(b)
    signb = int(math.copysign(1, fb))
    eps0 = 0

    for i in range(60):
        c = (a + b) / 2
        fc = fun(c)
        signc = int(math.copysign(1, fc))
        eps = abs(a - b)

        print(i, a, signa, b, signb, c, signc)
        a_arr.append(a)
        b_arr.append(b)
        c_aar.append(c)

        if eps < delta:
            break
        if signb * signc > 0:
            b = c
            signb = signc
        else:
            a = c
            signa = signc
        eps0 = eps
    return a_arr, b_arr, c_aar


def newton(x, delta):
    x_arr = []
    eps0 = 0

    #print(0, x)

    for i in range(1, 20):
        f = fun(x)
        df = dfun(x)
        x1 = x - f / df
        eps = abs(x1 - x)
        ksi = 2 * eps / (abs(x1) + delta);

        print(i, f, df, x1)
        x_arr.append(x1)

        if eps < delta or ksi < delta:
            break
        eps0 = eps
        x = x1
    return x_arr


a, b, c = bisection(0, 0.35, 1e-10)
print()
x = newton(0, 1e-10)
print()