import random

import tqdm


if __name__ == "__main__":
    for i in tqdm.tqdm(range(100)):
        # To something slow
        _ = [random.random() for _ in range(1000000)]
