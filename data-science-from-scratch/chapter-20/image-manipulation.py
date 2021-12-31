from matplotlib import pyplot as plt
import matplotlib.image as mpimg
import numpy as np
import pathlib

from sklearn.cluster import KMeans


if __name__ == "__main__":
    image_path = pathlib.Path(__file__).parent.resolve() / "test-image.jpeg"

    image = mpimg.imread(image_path) / 255
    w, h, d = original_shape = tuple(image.shape)
    assert d == 3
    # array of pixels
    image_array = np.reshape(image, (w * h, d))

    kmeans = KMeans(n_clusters=64, random_state=0)
    kmeans.fit(image_array)

    # array of predicted pixels
    labels = kmeans.predict(image_array)
    new_img = kmeans.cluster_centers_[labels].reshape(w, h, -1)

    plt.imshow(new_img)
    plt.show()
