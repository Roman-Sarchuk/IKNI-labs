import math


# ******************** functions ********************
def fun(x):
    return 0.4 * math.exp(-0.2 * x)


def derivative(x, h):
    d2 = (fun(x + h) - fun(x - h)) / (2 * h)
    d4 = (-fun(x + 2 * h) + 8 * fun(x + h) - 8 * fun(x - h) + fun(x - 2 * h)) / (12 * h)
    return h, d2, d4


def integral(u, v, n):
    s1 = 0
    s2 = 0
    h = (v - u) / n

    for i in range(1, n):
        s1 = s1 + fun(u + i * h)
    s1 = (s1 + (fun(u) - fun(v)) / 2) * h

    for i in range(1, int(n / 2)):
        s2 = s2 + (4 * fun(u + (2 * i - 1) * h) + 2.0 * fun(u + (2 * i) * h))
    s2 = (s2 + fun(u) - fun(v)) * h / 3

    return n, s1, s2


def relative_accuracy(true_value, approximate_value):
    return abs((true_value - approximate_value) / true_value) * 100


# ******************** calculation ********************
derivative_list = []        # [(h, d2, d4), ...]
derivative_value = -0.08
derivative_accuracy = {'d1': [], 'd2': []}
integral_list = []          # [(n, s1, s2), ...]
integral_value = 2
integral_accuracy = {'s1': [], 's2': []}

for i in range(0, 17):
    derivative_list.append(derivative(0, pow(10, -i)))
    derivative_accuracy['d1'].append(relative_accuracy(derivative_value, derivative_list[i][1]))
    derivative_accuracy['d2'].append(relative_accuracy(derivative_value, derivative_list[i][2]))

for i in range(0, 5):
    integral_list.append(integral(0, 10000, pow(10, i+1)))
    integral_accuracy['s1'].append(relative_accuracy(integral_value, integral_list[i][1]))
    integral_accuracy['s2'].append(relative_accuracy(integral_value, integral_list[i][2]))


# ******************** printing ********************
if __name__ == '__main__':
    print("derivative: (h, d2, d4)")
    for item in derivative_list:
        print(item)

    print()

    print("integral: (n, s1, s2)")
    for item in integral_list:
        print(item)
