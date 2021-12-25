import csv
import random
from typing import Dict, List, NamedTuple, Tuple

from dsfs.scratch.linear_algebra import Vector
from dsfs.scratch.machine_learning import split_data

from sklearn.neighbors import KNeighborsClassifier


class LabeledPoint(NamedTuple):
    point: Vector
    label: str


def parse_iris_row(row: List[str]) -> LabeledPoint:
    measurements = [float(value) for value in row[:-1]]
    label = row[-1].split("-")[-1]

    return LabeledPoint(measurements, label)


if __name__ == "__main__":
    random.seed(12)

    with open("chapter-12/iris.data") as f:
        reader = csv.reader(f)
        iris_data = [parse_iris_row(row) for row in reader]

    # The "training" set is the neighbors that we look at when choosing the k
    # nearest neighbors in the test set.
    iris_train, iris_test = split_data(iris_data, 0.70)

    classifier = KNeighborsClassifier(n_neighbors=5)
    classifier.fit([lp.point for lp in iris_train], [lp.label for lp in iris_train])

    score = classifier.score(
        [lp.point for lp in iris_test], [lp.label for lp in iris_test]
    )

    print(score)
