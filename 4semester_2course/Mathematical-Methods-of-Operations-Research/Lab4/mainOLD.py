class Solution:
    def __init__(self, matrix: list[list[int]]):
        self.matrix = matrix

    def wald_criterion(self):
        minimal_winning = [min(strategy) for strategy in self.matrix]
        return minimal_winning.index(max(minimal_winning)) + 1

    def savage_criterion(self):
        transpose_matrix = self.__transpose()
        maximum_winning = [max(assumption) for assumption in transpose_matrix]

        risk_matrix = [row[:] for row in self.matrix]

        for i in range(len(risk_matrix)):
            for j in range(len(risk_matrix)):
                risk_matrix[i][j] = maximum_winning[j] - risk_matrix[i][j]

        maximum_risking = [max(strategy) for strategy in risk_matrix]
        return maximum_risking.index(min(maximum_risking)) + 1

    def hurwitz_criterion(self, pessimism=0.5):
        minimal_winning = [min(strategy) for strategy in self.matrix]
        maximum_winning = [max(strategy) for strategy in self.matrix]
        h = [minimal_winning[i] * pessimism + maximum_winning[i] * (1 - pessimism) for i in range(len(self.matrix))]
        return h.index(max(h)) + 1

    def __transpose(self):
        transposed_matrix = []
        for i in range(len(self.matrix[0])):
            transposed_row = []
            for row in self.matrix:
                transposed_row.append(row[i])
            transposed_matrix.append(transposed_row)
        return transposed_matrix

# ===== DATA =====
winning_matrix = [
    [4, 39, 55, 14, 35, 38],
    [93, 97, 96, 43, 31, 34],
    [96, 2, 22, 22, 12, 24],
    [73, 4, 91, 55, 85, 83],
    [79, 38, 3, 98, 95, 25],
    [6, 79, 65, 68, 67, 59]
]

solution = Solution(winning_matrix)

# ===== SHOW RESULT =====
print("=== Result ===")
print("Wald optimal strategy:", solution.wald_criterion())
print("Savage optimal strategy:", solution.savage_criterion())
print("Hurwitz optimal strategy:", solution.hurwitz_criterion(0.5))
print("=== ====== ===")