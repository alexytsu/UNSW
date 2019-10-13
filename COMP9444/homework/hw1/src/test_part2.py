import pytest
import numpy as np

from part2 import LinearModel

class TestLinearModel:

    def test_activation_types(self):
        lm = LinearModel(0, 0)

        with pytest.raises(ValueError):
            lm.activation(True)

        with pytest.raises(ValueError):
            lm.activation([0.64])

        with pytest.raises(ValueError):
            lm.activation(np.array([0.64]))

        np_float = np.float64(0)
        assert lm.activation(np_float) == 0.5
        assert lm.activation(0) == 0.5
