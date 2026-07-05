import plotly.graph_objects as go
from main import *

# region --- Графік функції ---
# # Ініціаліхація масивів
# x, y, y1, y2, y4 = [], [], [], [], []
# for elm in euler_list:
#     x.append(elm[3])
#     y.append(elm[4])
#     y1.append(elm[2])
# for elm in heun_list:
#     y2.append(elm[3])
# for elm in runge_kutta_list:
#     y4.append(elm[5])
#
#
# # Створюємо графік
# fig = go.Figure()
#
# # Додаємо лінії для кожного з рішень
# fig.add_trace(go.Scatter(x=x, y=y, mode='lines+markers', name='y', line=dict(color='red')))
# fig.add_trace(go.Scatter(x=x, y=y1, mode='lines+markers', name='y1', line=dict(color='green')))
# fig.add_trace(go.Scatter(x=x, y=y2, mode='lines+markers', name='y2', line=dict(color='orange')))
# fig.add_trace(go.Scatter(x=x, y=y4, mode='lines+markers', name='y4', line=dict(color='blue')))
#
# # Налаштування логарифмічної шкали для осі Y
# # fig.update_yaxes(type="log")
#
# # Додаємо заголовки та підписи до осей
# fig.update_layout(
#     title="Графік функції",
#     xaxis_title="x",
#     yaxis_title="y",
#     legend_title="Легенда",
#     template="plotly_white"
# )
#
# # Показуємо графік
# fig.show()
# endregion


# region --- Графік абсолютної похибки обчислення ---
# Ініціаліхація масивів
x, d1, d2, d3 = [], [], [], []
for elm in euler_list:
    x.append(elm[3])
    d1.append(elm[5])
for elm in heun_list:
    d2.append(elm[6])
for elm in runge_kutta_list:
    d3.append(elm[8])


# Створюємо графік
fig = go.Figure()

# Додаємо лінії для кожного з рішень
fig.add_trace(go.Scatter(x=x, y=d1, mode='lines+markers', name='Δ1', line=dict(color='red')))
fig.add_trace(go.Scatter(x=x, y=d2, mode='lines+markers', name='Δ2', line=dict(color='green')))
fig.add_trace(go.Scatter(x=x, y=d3, mode='lines+markers', name='Δ3', line=dict(color='orange')))

# Налаштування логарифмічної шкали для осі Y
fig.update_yaxes(type="log")

# Додаємо заголовки та підписи до осей
fig.update_layout(
    title="Графік абсолютної похибки обчислення",
    xaxis_title="x",
    yaxis_title="y",
    legend_title="Легенда",
    template="plotly_white"
)

# Показуємо графік
fig.show()
# endregion
