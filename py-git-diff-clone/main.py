import re
import sys
import zlib

GIT_ROOT = "../"

"""
Three types of objects:

- commit:
- tree: folder on traditional filesystem (contains blobs and trees)
- blob: contains actual file contents

https://stackoverflow.com/questions/14790681/what-is-the-internal-format-of-a-git-tree-object

Refs are just pointers to objects

All objects are zlib compressed. I think that tree objects are encoded via
a binary format? See https://stackoverflow.com/a/33039114.
"""

def main():
    for filename in sys.argv[1:]:
        with open(filename, "rb") as compressed_file:
            data = zlib.decompress(compressed_file.read())

            print(data)

            # Works partially, but only under python2...
            # Also does not return the type of the object.
            # As far as I know, the type of the object should be included within
            # this file. Is it using the `40000`?
            entries = [
                line[0:2] + (line[2].encode("hex"),)
                for line in
                re.findall("(\d+) (.*?)\0(.{20})", data, re.MULTILINE)
            ]
            print(entries)


if __name__ == "__main__":
    main()
