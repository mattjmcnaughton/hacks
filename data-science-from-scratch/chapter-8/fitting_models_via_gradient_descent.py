import random
from typing import List

Vector = List[float]


# Copied from `src/scratch/linear_algebra.py`

def add(v: Vector, w: Vector) -> Vector:
    """Adds corresponding elements"""
    assert len(v) == len(w), "vectors must be the same length"

    return [v_i + w_i for v_i, w_i in zip(v, w)]

def scalar_multiply(c: float, v: Vector) -> Vector:
    """Multiplies every element by c"""
    return [c * v_i for v_i in v]

def vector_sum(vectors: List[Vector]) -> Vector:
    """Sums all corresponding elements"""
    # Check that vectors is not empty
    assert vectors, "no vectors provided!"

    # Check the vectors are all the same size
    num_elements = len(vectors[0])
    assert all(len(v) == num_elements for v in vectors), "different sizes!"

    return [sum(vector[i] for vector in vectors)
            for i in range(num_elements)]

def vector_mean(vectors: List[Vector]) -> Vector:
    """Computes the element-wise average"""
    n = len(vectors)
    return scalar_multiply(1/n, vector_sum(vectors))

## End copy

def linear_gradient(x: float, y: float, theta: Vector) -> Vector:
    slope, intercept = theta
    predicted = slope * x + intercept
    error = (predicted - y)
    grad = [2 * error * x, 2 * error]  # Gradient of the squared error function
    return grad

def gradient_step(v: Vector, gradient: Vector, step_size: float) -> Vector:
    """Moves `step_size` in the `gradient` direction from `v`."""
    assert len(v) == len(gradient)
    step = scalar_multiply(step_size, gradient)
    return add(v, step)

if __name__ == "__main__":
    # y = 20x + 5 - we want to find this value via gradient descent
    inputs = [(x, 20 * x + 5) for x in range(-50, 50)]

    # Start with random values for slope and intercept
    theta = [random.uniform(-1, 1), random.uniform(-1, 1)]

    # Size of step to take each time
    learning_rate = 0.001

    for epoch in range(5000):
        # Compute the mean of the gradients at all the different points
        linear_gradients = [linear_gradient(x, y, theta) for x, y in inputs]
        grad = vector_mean(linear_gradients)

        # Take a step in the direction
        theta = gradient_step(theta, grad, -learning_rate)
        print(epoch, theta)

    print(theta)
