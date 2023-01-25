# TODO

alphabet = "abcdefghijklmnopqrstuvwxyz"
alphabet2 = "ABCDEFGHIJKLMNOPQRSTUVWXYZ"


def count_letters(text):
    letters = 0     # Number of letters
    for i in range(len(text)):
        if text[i] in alphabet or text[i] in alphabet2:     # Check if is a letter
            letters += 1
    return letters


def count_words(text):
    spaces = 0          # Number of spaces

    for i in range(len(text)):
        if text[i] == " ":          # Check if it is a space
            spaces += 1

    return spaces + 1


def count_sentences(text):
    sentences = 0           # Number of sentences

    for i in range(len(text)):          # Check numbers of sentences
        if text[i] == "." or text[i] == "!" or text[i] == "?":
            sentences += 1

    return sentences


if __name__ == "__main__":

    text = input("Text: ")
    letters = count_letters(text)
    words = count_words(text)
    sentences = count_sentences(text)

    l = (letters / words) * 100     # L in the formula
    s = (sentences / words) * 100   # S in the formula

    g = 0.0588 * l - 0.296 * s - 15.8       se# Formula
    index = round(g)

    if index < 1:
        print("Before Grade 1")
    elif index >= 16:
        print("Grade 16+")
    else:
        print("Grade", index)