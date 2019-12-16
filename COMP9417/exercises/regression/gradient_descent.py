import numpy as np
from numpy import genfromtxt
import matplotlib.pyplot as plt


class Fit:
    def __init__(self, data_file: str, learning_rate=0.0001, epochs=100):
        self._data = genfromtxt(data_file, delimiter=",")
        self._m = 0
        self._c = 0
        self._rate = learning_rate
        self._epochs = epochs

    @property
    def data(self):
        return self._data

    @property
    def error(self):
        total_error = 0
        for point in self._data:
            x, y = point
            y_pred = self._m * x + self._c
            error = (y - y_pred) ** 2
            total_error += error

        return total_error / len(self._data)

    def calculate_y(self, x):
        return self._m * x + self._c

    def iterate(self):
        dm = sum(map(lambda x: -2 * x[0] * (x[1] - self.calculate_y(x[0])), self._data)) / len(self._data)
        dc = sum(map(lambda x: -2 * (x[1] - self.calculate_y(x[0])), self._data)) / len(
            self._data
        )
        self._m -= self._rate * dm
        self._c -= self._rate * dc

    def fit(self):
        for x in range(self._epochs):
            self.iterate()

    @property
    def x_endpoints(self):
        return min(self._data[:, 0]), max(self._data[:, 0])

    @property
    def y_endpoints(self):
        (x_0, x_1) = self.x_endpoints
        return self.calculate_y(x_0), self.calculate_y(x_1)



if __name__ == "__main__":
    fit = Fit("data1.csv", learning_rate=0.001)
    print("Initial")
    print("Data", fit.data)
    print("Error", fit.error)
    fit.fit()
    print("==============")

    def press(event):
        fit.fit()
        print("m", fit._m, "c", fit._c)
        plt.scatter(fit.data[:, 0], fit.data[:, 1])
        plt.plot(fit.x_endpoints, fit.y_endpoints)
        fig.canvas.draw()


    print("After training")
    print("Error", fit.error)
    plt.scatter(fit.data[:, 0], fit.data[:, 1])
    plt.plot(fit.x_endpoints, fit.y_endpoints, color="red")

    fig, ax = plt.subplots()
    fig.canvas.mpl_connect('key_press_event', press)

    plt.show()

