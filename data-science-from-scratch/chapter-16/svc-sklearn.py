import numpy as np
import matplotlib.pyplot as plt
from sklearn.svm import SVC
from sklearn.datasets import make_blobs


if __name__ == "__main__":
    # create 40 separable points
    X, y = make_blobs(n_samples=40, centers=2, random_state=6)

    # fit the model without regularization
    clf = SVC(kernel="linear", C=1000)
    clf.fit(X, y)

    # plot points
    plt.scatter(X[:, 0], X[:, 1], c=y, s=30, cmap=plt.cm.Paired)

    # plot the decision function
    ax = plt.gca()
    xlim = ax.get_xlim()
    ylim = ax.get_ylim()

    # create grid for evaluating model (needed to plot decision boundary and
    # margins)
    xx = np.linspace(xlim[0], xlim[1], 30)  # 30 points between x min and x max
    yy = np.linspace(ylim[0], ylim[1], 30)
    YY, XX = np.meshgrid(yy, xx)
    xy = np.vstack([XX.ravel(), YY.ravel()]).T
    Z = clf.decision_function(xy).reshape(XX.shape)

    # Draw decision boundary and margins
    ax.contour(
        XX,
        YY,
        Z,
        colors="k",
        levels=[-1, 0, 1],
        alpha=0.5,
        linestyles=["--", "-", "--"],
    )

    # plot the support vectors (points close to the plane)
    ax.scatter(
        clf.support_vectors_[:, 0],
        clf.support_vectors_[:, 1],
        s=100,
        linewidth=1,
    )

    plt.show()

    plt.show()
