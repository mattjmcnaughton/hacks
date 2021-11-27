from typing import List

import numpy as np
from scipy import optimize


Vector = List[float]


def sum_of_squares(x: Vector) -> Vector:
    return sum([i**2 for i in x])


def sum_of_squares_gradient(x: Vector) -> Vector:
    return np.asarray([2*i for i in x])


if __name__ == "__main__":
    x0 = np.asarray((3, 4, 6))

    print(optimize.fmin_cg(sum_of_squares, x0, fprime=sum_of_squares_gradient, full_output=True))
    # Can exclude `fprime` if I don't know it... scipy will estimate.
    print(optimize.fmin_cg(sum_of_squares, x0, full_output=True))
