# TODO
from cs50 import get_int


def pyramid(height):
    space = 0
    row = 0
    hash = 0

    while (row < height):
        space = height - (row + 1)
        result = ""                     # String of each line
        for i in range(0, space):       # Add spaces
            result += " "

        hash = row + 1

        for j in range(0, hash):        # Add hashes
            result += "#"

        result += "  "

        for k in range(0, hash):        # Add hashes
            result += "#"

        row += 1
        print(result)                   # Print the line


if __name__ == "__main__":

    height = get_int("Height: ")
    while ((height < 1 or height > 8)):
        height = get_int("Height: ")
    pyramid(height)