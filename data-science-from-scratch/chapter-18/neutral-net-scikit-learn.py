from sklearn.datasets import load_iris
from sklearn.model_selection import cross_val_score
from sklearn.neural_network import MLPClassifier


if __name__ == "__main__":
    X, y = load_iris(return_X_y=True)

    # MLP stands for multi-layer perceptron.
    clf = MLPClassifier(solver="sgd", random_state=1)
    print(cross_val_score(clf, X, y, cv=5))


