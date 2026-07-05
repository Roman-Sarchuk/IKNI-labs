#import plotly.graph_objects as go
import matplotlib.pyplot as plt
from main import *

gauss = gauss(A, B)
x0 = round(sum(gauss) / len(gauss), 1)

seidel = gauss_seidel(A, B, X0, delta)
i_arr = list(range(len(seidel)))
x1, x2, x3, x4, x5 = [], [], [], [], []
for x in seidel:
    x1.append(x[0])
    x2.append(x[1])
    x3.append(x[2])
    x4.append(x[3])
    x5.append(x[4])

# # Створюємо графік
# fig = go.Figure()
#
# # Додаємо лінії для кожного з рішень
# fig.add_trace(go.Scatter(x=i_arr, y=[x0 for i in range(len(i_arr))], mode='lines+markers', name='x', line=dict(color='red')))
# fig.add_trace(go.Scatter(x=i_arr, y=x1, mode='lines+markers', name='x1', line=dict(color='green')))
# fig.add_trace(go.Scatter(x=i_arr, y=x2, mode='lines+markers', name='x2', line=dict(color='orange')))
# fig.add_trace(go.Scatter(x=i_arr, y=x3, mode='lines+markers', name='x3', line=dict(color='yellow')))
# fig.add_trace(go.Scatter(x=i_arr, y=x4, mode='lines+markers', name='x4', line=dict(color='blue')))
# fig.add_trace(go.Scatter(x=i_arr, y=x5, mode='lines+markers', name='x5', line=dict(color='purple')))
#
# # Налаштування логарифмічної шкали для осі Y
# #fig.update_yaxes(type="log")
#
# # Додаємо заголовки та підписи до осей
# fig.update_layout(
#     title="Розв'язок СЛАР",
#     xaxis_title="i",
#     yaxis_title="x",
#     legend_title="Легенда",
#     template="plotly_white"
# )
#
# # Показуємо графік
# fig.show()

# fig.add_trace(go.Scatter(x=i_arr, y=[x0 for i in range(len(i_arr))], mode='lines+markers', name='x', line=dict(color='red')))
# fig.add_trace(go.Scatter(x=i_arr, y=x1, mode='lines+markers', name='x1', line=dict(color='green')))
# fig.add_trace(go.Scatter(x=i_arr, y=x2, mode='lines+markers', name='x2', line=dict(color='orange')))
# fig.add_trace(go.Scatter(x=i_arr, y=x3, mode='lines+markers', name='x3', line=dict(color='yellow')))
# fig.add_trace(go.Scatter(x=i_arr, y=x4, mode='lines+markers', name='x4', line=dict(color='blue')))
# fig.add_trace(go.Scatter(x=i_arr, y=x5, mode='lines+markers', name='x5', line=dict(color='purple')))

plt.plot(i_arr, [x0 for i in range(len(i_arr))], label='x', color='red')
plt.plot(i_arr, x1, label='x1', color='blue')
plt.plot(i_arr, x2, label='x2', color='orange')
plt.plot(i_arr, x3, label='x3', color='green')
plt.plot(i_arr, x4, label='x4', color='yellow')
plt.plot(i_arr, x5, label='x5', color='purple')

# Налаштування логарифмічної шкали для осі x (h)
plt.xscale('log')

# Налаштування заголовка та підписів
plt.title("Розв'язок СЛАР")
plt.xlabel("i")
plt.ylabel("x")

plt.legend(loc='center left', bbox_to_anchor=(1, 0.5))

# Показати графік
plt.grid(True)
plt.tight_layout()
plt.show()
