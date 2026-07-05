import matplotlib.pyplot as plt
from main import *

# Побудова графіка
n_list = []
for intg in integral_list:
    n_list.append(intg[0])

print(n_list)
print(integral_accuracy['s1'])
print(integral_accuracy['s2'])

plt.plot(n_list, integral_accuracy['s1'], label='derivative 1', color='red')
plt.plot(n_list, integral_accuracy['s2'], label='derivative 2', color='green')

# Налаштування логарифмічної шкали для осі x (h)
plt.xscale('log')

# Налаштування заголовка та підписів
plt.title("Відносна похибка обчислення інтеграла")
plt.xlabel("N (логарифмічна шкала)")
plt.ylabel("Відносна похибка δd1 та δd2")


# # Побудова графіка
# h_list = []
# for drv in derivative_list:
#     h_list.append(drv[0])
#
# print(h_list)
# print(derivative_accuracy['d1'])
# print(derivative_accuracy['d2'])
#
# plt.plot(h_list, derivative_accuracy['d1'], label='derivative 1', color='red')
# plt.plot(h_list, derivative_accuracy['d2'], label='derivative 2', color='green')
#
# # Налаштування логарифмічної шкали для осі x (h)
# plt.xscale('log')
#
# # Налаштування заголовка та підписів
# plt.title("Відносна похибка обчислення похідної")
# plt.xlabel("h (логарифмічна шкала)")
# plt.ylabel(" Відносна похибка δd1 та δd2")


plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Показати графік
plt.grid(True)
plt.tight_layout()
plt.show()
