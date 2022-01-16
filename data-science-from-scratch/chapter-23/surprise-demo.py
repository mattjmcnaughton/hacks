from surprise import Dataset, SVD
from surprise.model_selection import cross_validate


if __name__ == "__main__":
    # Movielens 100k dataset
    data = Dataset.load_builtin("ml-100k")

    algo = SVD()

    cross_validate(algo, data, measures=["RMSE"], cv=5, verbose=True)

