#!/usr/bin/env python3
"""
part2.py

UNSW COMP9444 Neural Networks and Deep Learning

ONLY COMPLETE METHODS AND CLASSES MARKED "TODO".

DO NOT MODIFY IMPORTS. DO NOT ADD EXTRA FUNCTIONS.
DO NOT MODIFY EXISTING FUNCTION SIGNATURES.
DO NOT IMPORT ADDITIONAL LIBRARIES.
DOING SO MAY CAUSE YOUR CODE TO FAIL AUTOMATED TESTING.

YOU MAY MODIFY THE LINE net = NetworkLstm().to(device)
"""

import numpy as np

import torch
import torch.nn as tnn
import torch.optim as topti

from torchtext import data
from torchtext.vocab import GloVe

import time
# Class for creating the neural network.
class NetworkLstm(tnn.Module):
    """
    Implement an LSTM-based network that accepts batched 50-d
    vectorized inputs, with the following structure:
    LSTM(hidden dim = 100) -> Linear(64) -> ReLu-> Linear(1)
    Assume batch-first ordering.
    Output should be 1d tensor of shape [batch_size].
    """

    def __init__(self):
        super(NetworkLstm, self).__init__()
        """
        Create and initialise weights and biases for the layers.
        """
        self.lstm = tnn.LSTM(
            input_size=50, hidden_size=100, batch_first=True
        )
        self.fc1 = tnn.Linear(100, 64)
        self.ReLU1 = tnn.ReLU()
        self.fc2 = tnn.Linear(64, 1)

    def forward(self, input, length):
        """
        DO NOT MODIFY FUNCTION SIGNATURE
        Create the forward pass through the network.
        """
        packed_input = tnn.utils.rnn.pack_padded_sequence(input, length, batch_first=True)
        x1, (hn, cn) = self.lstm(packed_input)
        x2 = self.fc1(hn[0])
        x2 = self.ReLU1(x2)
        x3 = self.fc2(x2)
        return x3[:,0]


# Class for creating the neural network.
class NetworkCnn(tnn.Module):
    """
    Implement a Convolutional Neural Network.
    All conv layers should be of the form:
    conv1d(channels=50, kernel size=8, padding=5)

    Conv -> ReLu -> maxpool(size=4) -> Conv -> ReLu -> maxpool(size=4) ->
    Conv -> ReLu -> maxpool over time (global pooling) -> Linear(1)

    The max pool over time operation refers to taking the
    maximum val from the entire output channel. See Kim et. al. 2014:
    https://www.aclweb.org/anthology/D14-1181/
    Assume batch-first ordering.
    Output should be 1d tensor of shape [batch_size].
    """

    def __init__(self):
        super(NetworkCnn, self).__init__()
        """
        Create and initialise weights and biases for the layers.
        """
        self.conv1 = tnn.Conv1d(in_channels=50, kernel_size=8, padding=5, out_channels=50)
        self.ReLU1 = tnn.ReLU()
        self.maxpool1 = tnn.MaxPool1d(4)
        self.conv2 = tnn.Conv1d(in_channels=50, kernel_size=8, padding=5, out_channels=50)
        self.ReLU2 = tnn.ReLU()
        self.maxpool2 = tnn.MaxPool1d(4)
        self.conv3 = tnn.Conv1d(in_channels=50, kernel_size=8, padding=5, out_channels=50)
        self.ReLU3 = tnn.ReLU()
        self.maxpoolglobal = tnn.AdaptiveMaxPool1d(50)
        self.fc1 = tnn.Linear(50*50, 1)



    def forward(self, input, length):
        """
        DO NOT MODIFY FUNCTION SIGNATURE
        Create the forward pass through the network.
        """
        x1 = self.conv1(input.permute(0,2,1))
        x1 = self.ReLU1(x1)
        x1 = self.maxpool1(x1)

        x2 = self.conv2(x1)
        x2 = self.ReLU2(x2)
        x2 = self.maxpool2(x2)

        x3 = self.conv3(x2)
        x3 = self.ReLU3(x3)
        x3 = self.maxpoolglobal(x3)

        x3 = x3.view(x3.shape[0], -1)

        output = self.fc1(x3)
        return output[:,0]



def lossFunc():
    """
    Return a loss function appropriate for the above networks that
    will add a sigmoid to the output and calculate the binary
    cross-entropy.
    """
    def customLoss(input, output):
        return tnn.functional.binary_cross_entropy_with_logits(input, output)

    return customLoss


def measures(outputs, labels):
    """
    Return (in the following order): the number of true positive
    classifications, true negatives, false positives and false
    negatives from the given batch outputs and provided labels.

    outputs and labels are torch tensors.
    """
    outputs[outputs <= 0] = 0
    outputs[outputs > 0] = 1
    confusion_vector = outputs / labels

    # true positives when label=1, truth=1: 1/1 = 1
    tp = torch.sum(confusion_vector == 1).item()

    # true negative when label=0, truth=0 : 0/0 = nan
    tn = torch.sum(torch.isnan(confusion_vector)).item()

    # false positive when label=1, truth=0: 1/0 = inf
    fp = torch.sum(torch.isinf(confusion_vector)).item()

    # false negative when label=0, truth=1: 0/1 = 0
    fn = torch.sum(confusion_vector == 0).item()

    return tp, tn, fp, fn


def main():
    # Use a GPU if available, as it should be faster.
    device = torch.device("cuda:0" if torch.cuda.is_available() else "cpu")
    print("Using device: " + str(device))

    print("Loading Data")
    # Load the training dataset, and create a data loader to generate a batch.
    textField = data.Field(lower=True, include_lengths=True, batch_first=True)
    labelField = data.Field(sequential=False)

    from imdb_dataloader import IMDB

    train, dev = IMDB.splits(textField, labelField, train="train", validation="dev")

    textField.build_vocab(train, dev, vectors=GloVe(name="6B", dim=50))
    labelField.build_vocab(train, dev)

    trainLoader, testLoader = data.BucketIterator.splits(
        (train, dev),
        shuffle=True,
        batch_size=64,
        sort_key=lambda x: len(x.text),
        sort_within_batch=True,
    )

    # Create an instance of the network in memory (potentially GPU memory). Can change to NetworkCnn during development.

    net = None

    useCNN = False
    if useCNN:
        print("Using CNN")
        net = NetworkCnn().to(device)
    else:
        print("Using RNN")
        net = NetworkLstm().to(device)
    
    print("Data Loaded")

    criterion = lossFunc()
    optimiser = topti.Adam(
        net.parameters(), lr=0.001
    )  # Minimise the loss using the Adam algorithm.

    for epoch in range(10):
        running_loss = 0

        for i, batch in enumerate(trainLoader):
            start_time = time.time()
            # Get a batch and potentially send it to GPU memory.
            inputs, length, labels = (
                textField.vocab.vectors[batch.text[0]].to(device),
                batch.text[1].to(device),
                batch.label.type(torch.FloatTensor).to(device),
            )

            labels -= 1

            # PyTorch calculates gradients by accumulating contributions to them (useful for
            # RNNs).  Hence we must manually set them to zero before calculating them.
            optimiser.zero_grad()

            # Forward pass through the network.
            output = net(inputs, length)

            loss = criterion(output, labels)

            # Calculate gradients.
            loss.backward()

            # Minimise the loss according to the gradient.
            optimiser.step()

            running_loss += loss.item()

            if i % 32 == 31:
                print(
                    "Epoch: %2d, Batch: %4d, Loss: %.3f, Trained in %.2fms"
                    % (epoch + 1, i + 1, running_loss / 32, (time.time()-start_time)*1000)
                )
                running_loss = 0

    true_pos, true_neg, false_pos, false_neg = 0, 0, 0, 0

    # Evaluate network on the test dataset.  We aren't calculating gradients, so disable autograd to speed up
    # computations and reduce memory usage.
    with torch.no_grad():
        for batch in testLoader:
            # Get a batch and potentially send it to GPU memory.
            inputs, length, labels = (
                textField.vocab.vectors[batch.text[0]].to(device),
                batch.text[1].to(device),
                batch.label.type(torch.FloatTensor).to(device),
            )

            labels -= 1

            outputs = net(inputs, length)

            tp_batch, tn_batch, fp_batch, fn_batch = measures(outputs, labels)
            true_pos += tp_batch
            true_neg += tn_batch
            false_pos += fp_batch
            false_neg += fn_batch

    accuracy = 100 * (true_pos + true_neg) / (true_pos + true_neg + false_neg + false_pos)
    matthews = MCC(true_pos, true_neg, false_pos, false_neg)

    print(
        "Classification accuracy: %.2f%%\n"
        "Matthews Correlation Coefficient: %.2f" % (accuracy, matthews)
    )


# Matthews Correlation Coefficient calculation.
def MCC(tp, tn, fp, fn):
    numerator = tp * tn - fp * fn
    denominator = ((tp + fp) * (tp + fn) * (tn + fp) * (tn + fn)) ** 0.5

    with np.errstate(divide="ignore", invalid="ignore"):
        return np.divide(numerator, denominator)


if __name__ == "__main__":
    main()
