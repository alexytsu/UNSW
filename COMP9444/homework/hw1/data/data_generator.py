#!/usr/bin/env python3
"""
PROVIDED FOR REFERNCE ONLY

Be aware that running this file will replace the provided file
./binary_classification_data.pkl
with a new one, and it's unlikely they will be the same.
"""

import numpy as np
import matplotlib.pyplot as plt
import pickle as pkl
import os

set1 = np.random.normal(0.2, 0.3, (25, 2))
set2 = np.random.normal(0.8, 0.3, (25, 2))

data = np.append(set1, set2, axis=0)

# close to origin = 0
# far away = 1
labels = np.asarray([1] * 25 + [0] * 25)

pkl.dump((data, labels), open("./binary_classification_data.pkl", "wb"))

inp, lb = pkl.load(open("./binary_classification_data.pkl", "rb"))
plt.scatter(inp[:, 0], inp[:, 1], c=lb)
plt.show()
