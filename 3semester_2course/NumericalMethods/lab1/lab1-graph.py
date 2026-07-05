import matplotlib.pyplot as plt

# Приклад списку похибок (замініть цей список на свої дані)
errors = [0.01, 0.005, 0.003, 0.002, 0.0015, 0.001, 0.0005]  # ваші дані

# Якщо у вас 100 записів, для осі X можна просто створити range від 1 до 100
steps = list(range(1, len(errors) + 1))

# Побудова графіка
plt.plot(steps, errors, marker='o', linestyle='-', color='b')

# Налаштування заголовка та підписів
plt.title("Графік абсолютних похибок")
plt.xlabel("Кроки циклу")
plt.ylabel("Абсолютні похибки")

# Показати графік
plt.grid(True)
plt.show()
