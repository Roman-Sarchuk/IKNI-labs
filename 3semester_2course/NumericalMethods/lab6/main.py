from math import e

y0 = 0.22
x0 = 0
x1 = 1
n = 20


def delta(y, y1):
    return abs(y - y1)


def fun(x, y):
    return -0.7 * y


def p_fun(x):
    return 0.21 * e ** (-0.7 * x)


def euler(y0, x0, x1, n):
    res_list = []
    y = y0
    x = x0
    h = (x1 - x0) / n
    #print(0, y, x)
    res_list.append((0, None, y, x, y0, None))

    for i in range(1, n + 1):
        k1 = fun(x, y)
        y = y + k1 * h
        x = x + h
        #print(i, k1, y, x)
        p = p_fun(x)
        res_list.append((i, k1, y, x, p, delta(p, y)))

    return res_list


def heun(y0, x0, x1, n):
    res_list = []
    y = y0
    x = x0
    h = (x1 - x0) / n
    #print(0, y, x)
    res_list.append((0, None, None, y, x, y0, None))

    for i in range(1, n + 1):
        k1 = fun(x, y);
        k2 = fun(x + h, y + h * k1)
        y = y + (k1 + k2) * h / 2
        x = x + h
        #print(i, k1, k2, y, x)
        p = p_fun(x)
        res_list.append((i, k1, k2, y, x, p, delta(p, y)))

    return res_list


def runge_kutta4(y0, x0, x1, n):
    res_list = []
    y = y0
    x = x0
    h = (x1 - x0) / n
    # print(0, y, x)
    res_list.append((0, None, None, None, None, y, x, y0, None))

    for i in range(1, n + 1):
        k1 = fun(x, y)
        k2 = fun(x + h / 2, y + k1 * h / 2)
        k3 = fun(x + h / 2, y + k2 * h / 2)
        k4 = fun(x + h, y + k3 * h)
        y = y + (k1 + 2 * k2 + 2 * k3 + k4) * h / 6
        x = x + h
        #print(i, k1, k2, k3, k4, y, x)
        p = p_fun(x)
        res_list.append((i, k1, k2, k3, k4, y, x, p, delta(p, y)))

    return res_list


euler_list = euler(y0, x0, x1, n)
#print()
heun_list = heun(y0, x0, x1, n)
#print()
runge_kutta_list = runge_kutta4(y0, x0, x1, n)
#print()
