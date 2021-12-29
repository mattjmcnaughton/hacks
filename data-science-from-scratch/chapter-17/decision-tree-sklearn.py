from sklearn.datasets import load_iris
from sklearn.model_selection import train_test_split, cross_val_score
from sklearn.tree import DecisionTreeClassifier, export_text
from sklearn.ensemble import RandomForestClassifier


if __name__ == "__main__":
    X, y = load_iris(return_X_y=True)

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.4, random_state=0)

    dt = DecisionTreeClassifier(criterion="entropy", random_state=0, max_depth=2)
    dt.fit(X_train, y_train)
    print(dt.score(X_test, y_test))

    rfc = RandomForestClassifier(criterion="entropy", n_estimators=10)
    rfc.fit(X_train, y_train)
    print(rfc.score(X_test, y_test))

    dt = DecisionTreeClassifier(criterion="entropy", random_state=0, max_depth=2)
    print(cross_val_score(dt, X, y, cv=5))
