lagrange1 = lambda x: (110 * x + 11) / 20
lagrange2 = lambda x: (-550 * x ** 2 + 385 * x + 33) / 60
lagrange3 = lambda x: (5500 * x ** 3 - 3300 * x ** 2 + 935 * x + 66) / 120
lagrange4 = lambda x: (-16500 * x ** 4 + 18700 * x ** 3 - 6435 * x ** 2 + 1133 * x + 66) / 120

xmin = 0.0
xmax = 0.6
points = 50
h = (xmax - xmin) / points

class Lagrange:
    dic = {'x': [], 'y1': [], 'y2': [], 'y3': [], 'y4': []}

    def fill(self):
        for i in range(points + 1):
            x = xmin + i * h
            y1 = lagrange1(x)
            y2 = lagrange2(x)
            y3 = lagrange3(x)
            y4 = lagrange4(x)

            self.dic['x'].append(x)
            self.dic['y1'].append(y1)
            self.dic['y2'].append(y2)
            self.dic['y3'].append(y3)
            self.dic['y4'].append(y4)