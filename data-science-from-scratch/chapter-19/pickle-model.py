import pathlib
import pickle

from sklearn.datasets import load_iris
from sklearn.model_selection import cross_val_score
from sklearn.neural_network import MLPClassifier


if __name__ == "__main__":
    X, y = load_iris(return_X_y=True)

    # MLP stands for multi-layer perceptron.
    clf = MLPClassifier(solver="sgd", random_state=1)
    clf.fit(X, y)

    pickle_path = pathlib.Path(__file__).parent.resolve() / "pickle_model.pkl"
    with open(pickle_path, "wb") as f:
        pickle.dump(clf, f)

    with open(pickle_path, "rb") as f:
        pickle_clf = pickle.load(f)

    print(pickle_clf.score(X, y))
