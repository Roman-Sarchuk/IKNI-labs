import math


class NewtonBackwardInterpolator:
    x_list = []
    y_list = []
    function = None
    calc_x = 0
    value_at_x = 0

    def __init__(self, x_list, function):
        self.set_values(x_list, function)

    def set_values(self, x_list, function):
        self.x_list = x_list
        self.function = function
        self.y_list = [function(x) for x in x_list]

    def get_finite_differences(self, n, i) -> float or None:
        if n == 0:
            return self.y_list[i]

        # verification
        if i >= len(self.y_list) - 1 or i < 0 or n < 0:
            return None

        # calculation
        if n == 1:
            return self.y_list[i+1] - self.y_list[i]
        else:
            try:
                return self.get_finite_differences(n - 1, i + 1) - self.get_finite_differences(n - 1, i)
            except TypeError:
                return None

    def __calc_t_part(self, k) -> float:
        res = 1
        n = len(self.x_list) - 1
        for i in range(k):
            res *= self.calc_x - self.x_list[n - i]
        return res / math.factorial(k)

    def calc(self, n, x) -> float or None:
        # verification
        if n >= len(self.x_list) or n < 0:
            return None

        self.calc_x = x

        # calculation
        res = 0
        for i in range(n + 1):
            res += self.__calc_t_part(i) * self.get_finite_differences(i, n - i)

        self.value_at_x = res
        return res

    def get_value_at_x(self):
        return self.value_at_x

    def get_absolute_error(self):
        return abs(self.function(self.calc_x) - self.value_at_x)

    def get_relative_error(self):
        return self.get_absolute_error() / abs(self.function(self.calc_x))


def func(x) -> float:
    return math.log(x)


if __name__ == '__main__':
    x1_list = [0.5, 1.5]
    x2_list = [4, 5, 6]
    x1 = 1.35
    x2 = 5.5

    first_order_polynomial = NewtonBackwardInterpolator(x1_list, func)
    first_order_polynomial.calc(1, x1)
    second_order_polynomial = NewtonBackwardInterpolator(x2_list, func)
    second_order_polynomial.calc(2, x2)

    print()

    print("\t:First order polynomial:")
    print(f"Exact value at point x={x1}: {func(x1)}")
    print(f"Approximate value at point x={x1}: {first_order_polynomial.get_value_at_x()}")
    print(f"Absolute error: {first_order_polynomial.get_absolute_error()}")
    print(f"Relative error: {first_order_polynomial.get_relative_error()}")

    print("\n\n")

    print("\t:Second order polynomial:")
    print(f"Exact value at point x={x2}: {func(x2)}")
    print(f"Approximate value at point x={x2}: {second_order_polynomial.get_value_at_x()}")
    print(f"Absolute error: {second_order_polynomial.get_absolute_error()}")
    print(f"Relative error: {second_order_polynomial.get_relative_error()}")

    print()
