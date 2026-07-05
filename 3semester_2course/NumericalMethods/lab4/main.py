def gauss(AA, BB):
    n = len(BB)
    A = []
    for aa in AA:
        A.append(aa[:])
    B = BB[:]

    # прямий хід алгоритму
    for k in range(n - 1):

        # визначення найбільшого елемента
        value = 0
        index = 0
        for i in range(k, n):
            if abs(A[i][k]) > value:
                value = abs(A[i][k])
                index = i

        # перестановка рядків
        A[k], A[index] = A[index], A[k]
        B[k], B[index] = B[index], B[k]

        # перевірка умови
        if A[k][k] == 0:
            print("Error: A[k][k] == 0")
            return

        # побудова трикутної матриці
        for i in range(k + 1, n):
            m = A[i][k] / A[k][k]
            for j in range(k, n):
                A[i][j] = A[i][j] - A[k][j] * m
            B[i] = B[i] - B[k] * m
        # print(k + 1)
        # print(A, B)

    # зворотній хід алгоритму
    X = B[:]
    X[n - 1] = B[n - 1] / A[n - 1][n - 1]
    for i in range(n - 2, -1, -1):
        for j in range(i + 1, n):
            X[i] = X[i] - A[i][j] * X[j]
        X[i] = X[i] / A[i][i]
    #print(X)
    return X


def gauss_seidel(A, B, X0, delta):
    res = []
    dimension = len(X0)
    X = X0[:]
    res.append(X0[:])
    #print(0, X)

    for k in range(1, 40):
        for i in range(dimension):
            X[i] = B[i]
            for j in range(dimension):
                if i != j:
                    X[i] = X[i] - A[i][j] * X[j]
            X[i] = X[i] / A[i][i]

        eps = []
        ksi = []
        for i in range(dimension):
            eps.append(abs(X[i] - X0[i]))
            ksi.append(eps[i] / (abs(X[i]) + delta))
        X0 = X[:]
        eps_max = 0
        ksi_max = 0
        for i in range(dimension):
            if eps_max < eps[i]: eps_max = eps[i]
            if ksi_max < ksi[i]: ksi_max = ksi[i]

        print(k, X)
        res.append(X[:])

        if eps_max < delta and ksi_max < delta:
            break
    return res


A = [[1, 1, 1, 1, 1],
     [0, 1.3, -0.1, -0.5, -0.5],
     [0, -0.6, 2.1, 0, -0.6],
     [-0.2, -0.4, -0.9, 0.7, 0],
     [-0.3, -0.2, -0.5, -0.2, 1.5]]

B = [10.5, 0.42, 1.89, -1.68, 0.63]
X0 = [0 for i in range(5)]
delta = 1e-10

if __name__ == '__main__':
    gauss(A, B)

    gauss_seidel(A, B, X0, delta)


    def is_diag_dominant(A):
        for i in range(len(A)):
            diag_elem = abs(A[i][i])
            sum_other = sum(abs(A[i][j]) for j in range(len(A)) if j != i)
            if diag_elem < sum_other:
                return False
        return True


    print("Матриця A діагонально домінуюча:", is_diag_dominant(A))