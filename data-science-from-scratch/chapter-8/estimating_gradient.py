from typing import Callable, List


Vector = List[float]


def difference_quotient(f: Callable[[float], float],
                        x: float,
                        h: float) -> float:
    """As h becomes smaller and smaller, we get closer and closer to the
    derivative.

    Very computationally expensive, but shows the elements.
    """
    return (f(x + h) - f(x)) / h


def partial_difference_quotient(f: Callable[[float], float],
                                v: Vector,
                                i: int,
                                h: float) -> float:
    """As h becomes smaller and smaller, we get closer and closer to the
    derivative.

    Very computationally expensive, but shows the elements.
    """
    w = [
        v_j + (h if j == i else 0)
        for j, v_j in enumerate(v)
    ]

    return (f(w) - f(v)) / h


def estimate_gradient(f: Callable[[Vector], float],
                      v: Vector,
                      h: float = 0.00001):
    return [
        partial_difference_quotient(f, v, i, h)
        for i in range(len(v))
    ]


def square(x: float) -> float:
    return x * x


def derivative(x: float) -> float:
    return 2 * x


def plot(xs: List[int], actuals: List[float], estimates: List[float]):
    import matplotlib.pyplot as plt
    plt.title("Actual derivatives vs estimates")
    plt.plot(xs, actuals, 'rx', label='Actual')
    plt.plot(xs, estimates, 'b+', label='Estimate')
    plt.legend(loc=9)
    plt.show()


def compare_difference_quotient_and_derivative():
    xs = range(-10 , 11)
    actuals = [derivative(x) for x in xs]
    estimates = [difference_quotient(square, x, h=0.000001) for x in xs]

    plot(xs, actuals, estimates)

if __name__ == "__main__":
    compare_difference_quotient_and_derivative()
