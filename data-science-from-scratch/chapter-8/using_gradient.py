import math
import random
from typing import List

Vector = List[float]


# ===== Copied from `src/scratch/linear_algebra.py` - should determine how to
# import.


def add(v: Vector, w: Vector) -> Vector:
    """Adds corresponding elements"""
    assert len(v) == len(w), "vectors must be the same length"

    return [v_i + w_i for v_i, w_i in zip(v, w)]

def scalar_multiply(c: float, v: Vector) -> Vector:
    """Multiplies every element by c"""
    return [c * v_i for v_i in v]

def dot(v: Vector, w: Vector) -> float:
    """Computes v_1 * w_1 + ... + v_n * w_n"""
    assert len(v) == len(w), "vectors must be same length"

    return sum(v_i * w_i for v_i, w_i in zip(v, w))

def sum_of_squares(v: Vector) -> float:
    """Returns v_1 * v_1 + ... + v_n * v_n"""
    return dot(v, v)


def subtract(v: Vector, w: Vector) -> Vector:
    """Subtracts corresponding elements"""
    assert len(v) == len(w), "vectors must be the same length"

    return [v_i - w_i for v_i, w_i in zip(v, w)]

def squared_distance(v: Vector, w: Vector) -> float:
    """Computes (v_1 - w_1) ** 2 + ... + (v_n - w_n) ** 2"""
    return sum_of_squares(subtract(v, w))

def distance(v: Vector, w: Vector) -> float:
    """Computes the distance between v and w"""
    return math.sqrt(squared_distance(v, w))


################# End copy


def gradient_step(v: Vector, gradient: Vector, step_size: float) -> Vector:
    """Moves `step_size` in the `gradient` direction from `v`."""
    assert len(v) == len(gradient)
    step = scalar_multiply(step_size, gradient)
    return add(v, step)


# Sum of squares is the function that we seek to minimize (i.e. x^2 + y^2 +
# z^2). In this context, we can calculate its gradient using math (2x + 2y +
# 2z), but if we couldn't we could estimate using a difference quotient (it'd just
# be very expensive to do so).
def sum_of_squares_gradient(v: Vector) -> Vector:
    return [2 * v_i for v_i in v]


if __name__ == "__main__":
    # Choose a random starting point (x, y, z)
    v = [random.uniform(-10, 10) for i in range(3)]

    num_epochs = 1000
    for epoch in range(num_epochs):
        grad = sum_of_squares_gradient(v)  # Compute gradient at v - in this case, we use math, but we could also estimate the gradient.
        v = gradient_step(v, grad, -0.01)  # Take a negative gradient step
        print(epoch, v)

    true_minimum = [0, 0, 0]
    print(distance(v, true_minimum))
