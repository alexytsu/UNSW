#!/usr/bin/env python3
"""
part1.py

UNSW COMP9444 Neural Networks and Deep Learning

ONLY COMPLETE METHODS AND CLASSES MARKED "TODO".

DO NOT MODIFY IMPORTS. DO NOT ADD EXTRA FUNCTIONS.
DO NOT MODIFY EXISTING FUNCTION SIGNATURES.
DO NOT IMPORT ADDITIONAL LIBRARIES.
DOING SO MAY CAUSE YOUR CODE TO FAIL AUTOMATED TESTING.
"""
import torch

# Simple addition operation


def simple_addition(x, y):
    return torch.add(x, y)


# Resize tensors
# Use view() to implement the following functions ( flatten() and reshape() are not allowed )

def simple_reshape(x, shape):
    return x.view(shape)


def simple_flat(x):
    return x.view(-1)


# Transpose and Permutation

def simple_transpose(x):
    """ A function that swaps the first dimension and the second dimension of the given matrix x and returns the result. """
    return x.transpose(0, 1)


def simple_permute(x, order):
    """ A function that permutes the dimensions of the given tensor x according to the given order and returns the result. """
    return x.permute(order)


# Matrix multiplication (with broadcasting).

def simple_dot_product(x, y):
    """ A function that computes the dot product of two rank 1 tensors and returns the result. """
    return torch.dot(x, y)


def simple_matrix_mul(x, y):
    """ A function that performs a matrix multiplication of two given rank 2 tensors and returns the result. """
    return torch.mm(x, y)


def broadcastable_matrix_mul(x, y):
    """ A function that computes the broadcastable matrix product of two tensors and returns the result. """
    return torch.matmul(x, y)


# Concatenate and stack.
def simple_concatenate(tensors):
    """ A function that concatenates the given sequence of tensors in the first dimension and returns the result """
    return torch.cat(tensors, 0)


def simple_stack(tensors, dim):
    """ A function that concatenates the given sequence of tensors along a new dimension(dim) and returns the result. """
    return torch.cat(tensors, dim)
