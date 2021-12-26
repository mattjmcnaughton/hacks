import glob
import pathlib
import random
from typing import List, NamedTuple

from dsfs.scratch.machine_learning import split_data

from sklearn.feature_extraction.text import CountVectorizer
from sklearn.naive_bayes import (
    MultinomialNB,
)  # Could use Bernoulli, but would have binary-value for rather word included, not counts


class Message(NamedTuple):
    text: str
    is_spam: bool


def extract_data() -> List[Message]:
    data = []

    path = pathlib.Path(__file__).parent.resolve() / "spam_data" / "*" / "*"

    for filename in glob.glob(str(path)):
        is_spam = "ham" not in filename

        with open(filename, errors="ignore") as email_file:
            for line in email_file:
                if line.startswith("Subject:"):
                    subject = line.lstrip("Subject: ")
                    data.append(Message(subject, is_spam))
                    break

    return data


def generate_features_and_labels(vectorizer, training_data, test_data):
    # Only use `fit_transform` for the training. For the `test` set, want to
    # just use `transform`.
    training_X = vectorizer.fit_transform([td.text for td in training_data])
    test_X = vectorizer.transform([td.text for td in test_data])

    training_y = [td.is_spam for td in training_data]
    test_y = [td.is_spam for td in test_data]

    return training_X, test_X, training_y, test_y


def calculate_spammiest_words(classifier, vectorizer):
    class_labels = mn_clf.classes_  # is_spam = [False, True]
    feature_names = vectorizer.get_feature_names_out()

    ordered_non_spam_features = sorted(
        zip(mn_clf.feature_count_[0], feature_names), reverse=True
    )
    ordered_spam_features = sorted(
        zip(mn_clf.feature_count_[1], feature_names), reverse=True
    )

    top_1000_non_spam_features = set((list(zip(*ordered_non_spam_features))[1][:1000]))
    top_100_spam_features = set((list(zip(*ordered_spam_features))[1][:100]))

    return [f for f in top_100_spam_features if f not in top_1000_non_spam_features]


if __name__ == "__main__":
    random.seed(12)

    data = extract_data()
    training_data, test_data = split_data(data, 0.75)

    vectorizer = CountVectorizer()
    mn_clf = MultinomialNB()

    training_X, test_X, training_y, test_y = generate_features_and_labels(
        vectorizer, training_data, test_data
    )

    mn_clf.fit(training_X, training_y)

    model_score = mn_clf.score(test_X, test_y)
    spammiest_words = calculate_spammiest_words(mn_clf, vectorizer)

    print(f"Model score is: {model_score}")
    print(f"Spammiest words are: {spammiest_words}")
