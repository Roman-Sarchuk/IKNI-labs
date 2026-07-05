import matplotlib.pyplot as plt
from main import Lagrange

lagrange = Lagrange()
lagrange.fill()

# Побудова графіка
plt.plot(lagrange.dic['x'], lagrange.dic['y1'], label='lagrange 1', color='blue')
plt.plot(lagrange.dic['x'], lagrange.dic['y2'], label='lagrange 2', color='green')
plt.plot(lagrange.dic['x'], lagrange.dic['y3'], label='lagrange 3', color='red')
plt.plot(lagrange.dic['x'], lagrange.dic['y4'], label='lagrange 4', color='orange')

# Налаштування заголовка та підписів
plt.title("Інтерполяція функції")
plt.xlabel("колонка «Y»")
plt.ylabel("колонка «X»")

plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Показати графік
plt.grid(True)
plt.tight_layout()
plt.show()
