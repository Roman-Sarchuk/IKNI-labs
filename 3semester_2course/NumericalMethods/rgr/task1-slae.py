import time


class SLAE:
    A = [[-11, 1, -6, -3],
         [-6, 15, -4, 3],
         [1, 1, 11, 1],
         [-4, 1, 1, -11]]
    d = [-9, 4, -2, 4]
    x = [None, None, None, None]
    n = 4

    @staticmethod
    def print_matrix(matrix, lable):
        width = max(len(str(matrix[0])), len(str(matrix[len(matrix)-1])))

        print(f"{lable}:", "-" * (width - 2 - len(lable)))
        for row in matrix:
            print(row)
        print("-" * width)


class GaussianCholesky(SLAE):
    C = [[None, 0, 0, 0],
         [None, None, 0, 0],
         [None, None, None, 0],
         [None, None, None, None]]
    B = [[1, None, None, None],
         [0, 1, None, None],
         [0, 0, 1, None],
         [0, 0, 0, 1]]
    y = [None, None, None, None]

    def _sum_c(self, k, i) -> float:
        acc_sum = 0

        for j in range(i):
            acc_sum += self.C[k][j] * self.B[j][i]

        return acc_sum

    def _sum_b(self, k, i) -> float:
        acc_sum = 0

        for j in range(i):
            acc_sum += self.C[i][j] * self.B[j][k]

        return acc_sum

    def _sum_y(self, i) -> float:
        acc_sum = 0

        for j in range(i):
            acc_sum += self.C[i][j] * self.y[j]

        return acc_sum

    def _sum_x(self, index) -> float:
        acc_sum = 0

        for j in range(index + 1, self.n):
            acc_sum += self.B[index][j] * self.x[j]

        return acc_sum

    def _initialize_forward_step(self):
        for i in range(self.n):
            self.C[i][0] = self.A[i][0]
            if i != 0:
                self.B[0][i] = self.A[0][i] / self.A[0][0]

        self.y[0] = self.d[0] / self.A[0][0]

    def _forward_elimination_step(self):
        for i in range(1, self.n):
            for k in range(i, self.n):
                self.C[k][i] = self.A[k][i] - self._sum_c(k, i)
                if k != i:
                    self.B[i][k] = (self.A[i][k] - self._sum_b(k, i)) / self.C[i][i]
            self.y[i] = (self.d[i] - self._sum_y(i)) / self.C[i][i]

    def _backward_substitution(self):
        index = self.n - 1
        self.x[index] = self.y[index]
        index -= 1
        while index >= 0:
            self.x[index] = self.y[index] - self._sum_x(index)
            index -= 1

    def calc(self):
        self._initialize_forward_step()
        self._forward_elimination_step()
        self._backward_substitution()


class Seidel(SLAE):
    """
    x1 = b1/a11 + a12/a11*x2 + a13/a11*x3 + a14/a11*x4
    x2 = b2/a22 + a21/a22*x1 + a23/a22*x3 + a24/a22*x4
    x3 = b3/a33 + a31/a33*x1 + a32/a33*x2 + a34/a33*x4
    x4 = b4/a44 + a41/a44*x1 + a42/a44*x2 + a43/a44*x3
    """
    S = [[None, None, None, None],
         [None, None, None, None],
         [None, None, None, None],
         [None, None, None, None]]
    # X is a copy of 'd' when initialized
    iteration_count = 3
    x_iteration_list = []

    def __init__(self):
        self.x = self.d.copy()

        for i in range(self.n):
            self.S[i][0] = self.d[i] / self.A[i][i]
            k = 1
            for j in range(self.n):
                if j != i:
                    self.S[i][k] = -(self.A[i][j] / self.A[i][i])
                    k += 1

    def calc(self):
        self.x_iteration_list.append(self.x.copy())
        for _ in range(self.iteration_count):
            for i in range(self.n):
                acc_sum = self.S[i][0]
                k = 0
                for j in range(1, self.n):
                    if k == i:
                        k += 1
                    acc_sum += self.S[i][j] * self.x[k]
                    k += 1
                self.x[i] = acc_sum
            self.x_iteration_list.append(self.x.copy())

    def info(self):
        end_i = len(self.x_iteration_list) - 1
        for i in range(end_i + 1):
            print(f"X({i}) = {self.x_iteration_list[i]}")
            if i != end_i:
                print()


class MathErrorSLAE:
    def __init__(self, x_gh: list, x_sd: list):
        self._x_gh = x_gh
        self._x_sd = x_sd
        self.absolute = []
        self.relative = []

    def calc(self):
        for i in range(len(self._x_gh)):
            self.absolute.append(abs(self._x_gh[i] - self._x_sd[i]))

            if self._x_gh[i] != 0:
                self.relative.append((self.absolute[i] / abs(self._x_gh[i])))
            else:
                self.relative.append(float('inf'))

    def info(self):
        print(f"Absolute = {self.absolute}")
        print(f"Relative = {self.relative}")


if __name__ == '__main__':
    gh = GaussianCholesky()
    print("\n\n:Start:")
    start_time = time.perf_counter()
    gh.calc()
    end_time = time.perf_counter()
    print("X =", gh.x)
    print(":Finish:")
    print(f"time -> {(end_time - start_time):.8f}", )
    ###
    print()
    gh.print_matrix(gh.C, "C")
    print()
    gh.print_matrix(gh.B, "B")
    print()
    print("Y =", gh.y)
    print("\n\n\n")

    # ------------------------------------------------------

    sd = Seidel()
    print(":Start:")
    start_time = time.perf_counter()
    sd.calc()
    end_time = time.perf_counter()
    sd.info()
    print(":Finish:")
    print(f"time -> {(end_time - start_time):.8f}", )
    print("\n\n\n")

    # ------------------------------------------------------

    print(":Errors:")
    err = MathErrorSLAE(gh.x, sd.x)
    err.calc()
    err.info()
    print("\n\n\n")
