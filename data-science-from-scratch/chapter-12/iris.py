from collections import Counter, defaultdict
import csv
import random
from typing import Dict, List, NamedTuple, Tuple

from dsfs.scratch.linear_algebra import Vector, distance
from dsfs.scratch.machine_learning import split_data

class LabeledPoint(NamedTuple):
    point: Vector
    label: str

def majority_vote(labels: List[str]) -> str:
    vote_counts = Counter(labels)
    winner, winner_count = vote_counts.most_common(1)[0]
    num_winners = len([count for count in vote_counts.values() if count == winner_count])

    if num_winners == 1:
        return winner
    else:
        return majority_vote(labels[:-1])


def knn_classify(k: int, labeled_points: List[LabeledPoint], new_point: Vector) -> str:
    by_distance = sorted(labeled_points, key=lambda lp: distance(lp.point, new_point))

    # Find the labels for the k closest
    k_nearest_labels = [lp.label for lp in by_distance[:k]]

    return majority_vote(k_nearest_labels)

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

    k = 5  # Could have separate validation set for k size, but for now, just choose 5.

    # track how many times we see predicted vs actual
    confusion_matrix: Dict[Tuple[str, str], int] = defaultdict(int)
    num_correct = 0

    for iris in iris_test:
        predicted = knn_classify(k, iris_train, iris.point)
        actual = iris.label

        if predicted == actual:
            num_correct += 1

        confusion_matrix[(predicted, actual)] += 1

    pct_correct = num_correct / len(iris_test)
    print(pct_correct, confusion_matrix)

