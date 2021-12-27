import numpy as np
from sklearn.linear_model import Lasso, LinearRegression


def linear():
    X = np.array([
        [1, 1],
        [1, 2],
        [2, 2],
        [2, 3],
    ])
    y= np.dot(X, np.array([1, 2])) + 3

    reg = LinearRegression()
    reg.fit(X, y)

    print(reg.score(X, y))
    print(reg.coef_)
    print(reg.intercept_)
    print(reg.predict(np.array([[3, 5]])))


def lasso():
    n_samples, n_features = 10, 100
    rng = np.random.RandomState(0)
    y = rng.randn(n_samples)
    X = rng.randn(n_samples, n_features)

    # Lasso performs regulation by adding a penalty for each parameter
    clf = Lasso(alpha=0.5)
    clf.fit(X, y)

    print(clf.coef_)
    print(len(clf.coef_[clf.coef_ != 0]))


if __name__ == "__main__":
    linear()
    lasso()
