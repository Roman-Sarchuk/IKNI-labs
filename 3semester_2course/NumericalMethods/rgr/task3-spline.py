import numpy as np

class CubicSplineInterpolator:
    x_list = []
    y_list = []
    coeffs = []  # Коефіцієнти сплайну
    calc_x = 0
    value_at_x = 0

    def __init__(self, x_list, y_list):
        self.set_values(x_list, y_list)

    def set_values(self, x_list, y_list):
        # Ініціалізація точок
        self.x_list = x_list
        self.y_list = y_list
        self.__compute_spline_coeffs()

    def __compute_spline_coeffs(self):
        n = len(self.x_list) - 1  # Кількість інтервалів
        h = [self.x_list[i+1] - self.x_list[i] for i in range(n)]  # Довжина кожного інтервалу

        # Формуємо систему лінійних рівнянь для кубічного сплайну
        A = np.zeros((n + 1, n + 1))
        b = np.zeros(n + 1)

        # Внутрішні умови
        for i in range(1, n):
            A[i][i-1] = h[i-1]
            A[i][i] = 2 * (h[i-1] + h[i])
            A[i][i+1] = h[i]
            b[i] = 3 * ((self.y_list[i+1] - self.y_list[i]) / h[i] - (self.y_list[i] - self.y_list[i-1]) / h[i-1])

        # Крайові умови для натурального сплайну (другі похідні на кінцях дорівнюють нулю)
        A[0][0], A[n][n] = 1, 1

        # Розв'язок системи
        c = np.linalg.solve(A, b)

        # Обчислення коефіцієнтів a, b, c, d для кожного поліному
        self.coeffs = []
        for i in range(n):
            a = self.y_list[i]
            b = (self.y_list[i+1] - self.y_list[i]) / h[i] - h[i] * (2 * c[i] + c[i+1]) / 3
            d = (c[i+1] - c[i]) / (3 * h[i])
            self.coeffs.append((a, b, c[i], d))

    def __get_spline_value(self, x, i):
        # Обчислення значення сплайну в інтервалі
        a, b, c, d = self.coeffs[i]
        dx = x - self.x_list[i]
        return a + b * dx + c * dx**2 + d * dx**3

    def calc(self, x) -> float or None:
        # Знаходження індексу інтервалу
        if x < self.x_list[0] or x > self.x_list[-1]:
            return None  # x поза інтерполяційним діапазоном

        # Пошук інтервалу для x
        i = next(i for i in range(len(self.x_list) - 1) if self.x_list[i] <= x <= self.x_list[i+1])
        self.calc_x = x
        self.value_at_x = self.__get_spline_value(x, i)
        return self.value_at_x

    def get_value_at_x(self):
        return self.value_at_x


if __name__ == '__main__':
    # Приклад даних
    x_points = [0, 1, 2, 3, 4]
    y_points = [1, 2, 0, 2, 3]
    interpolator = CubicSplineInterpolator(x_points, y_points)

    # Точка для обчислення значення
    x_to_calc = 2.5
    result = interpolator.calc(x_to_calc)

    print(f"Значення в точці x={x_to_calc}: {result}")
