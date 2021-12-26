from io import BytesIO
import requests
import tarfile


BASE_URL = "https://spamassassin.apache.org/old/publiccorpus/"
FILES = [
    "20021010_easy_ham.tar.bz2",
    "20021010_hard_ham.tar.bz2",
    "20021010_spam.tar.bz2",
]

OUTPUT_DIR = "spam_data"

def download():
    for filename in FILES:
        content = requests.get(f"{BASE_URL}/{filename}").content

        fin = BytesIO(content)

        with tarfile.open(fileobj=fin, mode='r:bz2') as tf:
            tf.extractall(OUTPUT_DIR)


if __name__ == "__main__":
    download()
