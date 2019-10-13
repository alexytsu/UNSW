#!/usr/bin/env python3
"""
part2.py

UNSW COMP9444 Neural Networks and Deep Learning

ONLY COMPLETE METHODS AND CLASSES MARKED "TODO".

DO NOT MODIFY IMPORTS. DO NOT ADD EXTRA FUNCTIONS.
DO NOT MODIFY EXISTING FUNCTION SIGNATURES.
DO NOT IMPORT ADDITIONAL LIBRARIES.
DOING SO MAY CAUSE YOUR CODE TO FAIL AUTOMATED TESTING.
"""
import numpy as np
import pickle as pkl
import matplotlib.pyplot as plt


class LinearModel:
    def __init__(self, num_inputs, learning_rate):
        """
        Model is very similar to the Perceptron shown in Lectures 1c, slide 12, except that:
        (1) the bias is indexed by w(n+1) rather than w(0), and
        (2) the activation function is a (continuous) sigmoid rather than a (discrete) step function.

        x1 ----> * w1 ----\
        x2 ----> * w2 -----\
        x3 ----> * w3 ------\
        ...
                             \
        xn ----> * wn -------+--> s --> activation ---> z
        1  ----> * w(n+1) --/
        """
        self.num_inputs = num_inputs
        self.lr = learning_rate
        self.weights = np.asarray([1.0, -1.0, 0.0])  # Initialize as straight line

    def activation(self, x):
        """
        A sigmoid activation function that accepts a float and returns a float
        """
        if isinstance(x, (list, bool, np.ndarray)):
            raise ValueError(f"Activation function expects a float but got {type(x)} instead")

        return 1 / (1 + np.exp(-x))


    def forward(self, inputs):
        """
        the forward pass (inference) of a the model.
        """
        s = self.weights[-1]
        for index in range(self.num_inputs):
            s += inputs[index] * self.weights[index]

        return self.activation(s)

    @staticmethod
    def loss(prediction, label):
        """ Returns the cross entropy for the given prediction and label """
        E = -label * np.log(prediction) - (1 - label) * np.log(1 - prediction)
        return E

    @staticmethod
    def error(prediction, label):
        """ Return the difference between the label and the prediction
        For example, if label= 1 and the prediction was 0.8, return 0.2
                     if label= 0 and the preduction was 0.43 return -0.43
        """
        return label - prediction

    def backward(self, inputs, diff):
        """
        Adjust self.weights by gradient descent using a simplification
        """

        for i in range(self.num_inputs):
            self.weights[i] += self.lr * diff * inputs[i]
        
        self.weights[-1] += self.lr * diff



    def plot(self, inputs, marker):
        """
        Plot the data and the decision boundary
        """
        xmin = inputs[:, 0].min() * 1.1
        xmax = inputs[:, 0].max() * 1.1
        ymin = inputs[:, 1].min() * 1.1
        ymax = inputs[:, 1].max() * 1.1

        x = np.arange(xmin * 1.3, xmax * 1.3, 0.1)
        plt.scatter(inputs[:25, 0], inputs[:25, 1], c="C0", edgecolors='w', s=100)
        plt.scatter(inputs[25:, 0], inputs[25:, 1], c="C1", edgecolors='w', s=100)

        plt.xlim((xmin, xmax))
        plt.ylim((ymin, ymax))
        plt.plot(x, -(self.weights[0] * x + self.weights[2]) / self.weights[1], marker, alpha=0.6)
        plt.title("Data and decision boundary")
        plt.xlabel("x1")
        plt.ylabel("x2").set_rotation(0)


def main():
    inputs, labels = pkl.load(open("../data/binary_classification_data.pkl", "rb"))

    epochs = 400
    model = LinearModel(num_inputs=inputs.shape[1], learning_rate=0.01)

    for i in range(epochs):
        num_correct = 0
        cost = 0
        for x, y in zip(inputs, labels):
            # Get prediction
            output = model.forward(x)

            # Calculate loss
            cost += model.loss(output, y)

            # Calculate difference or differential
            diff = model.error(output, y)

            # Update the weights
            model.backward(x, diff)

            # Record accuracy
            preds = output > 0.5  # 0.5 is midline of sigmoid
            num_correct += int(preds == y)

        print(f" Cost: {cost/len(inputs):.2f} Accuracy: {num_correct / len(inputs) * 100:.2f}%")
        model.plot(inputs, "C2--")
    model.plot(inputs, "k")
    plt.show()


if __name__ == "__main__":
    main()
