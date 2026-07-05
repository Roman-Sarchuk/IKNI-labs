import matplotlib.pyplot as plt
from main import *

# Отримання масивів
# i = list(range(len(a)))
i = list(range(len(x)))

# Зазначення точок
# plt.plot(i, a, label='a', color='blue')
# plt.plot(i, b, label='b', color='green')
# plt.plot(i, c, label='c', color='orange')
# plt.plot(i, [0.21 for _ in i], label='x2', color='red')

plt.plot(i, x, label='xi', color='green')
plt.plot(i, [0.21 for _ in i], label='x2', color='red')

# Налаштування логарифмічної шкали для осі x (h)
# plt.xscale('log')

# Налаштування заголовка та підписів
plt.title("")
plt.xlabel("")
plt.ylabel("")

plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Показати графік
plt.grid(True)
plt.tight_layout()
plt.show()
