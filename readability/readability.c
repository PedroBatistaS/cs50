#include <cs50.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <math.h>



int count_letters(string text)
{
    int letters = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            letters++; // Counts letter
        }
    }
    return letters;
}

int count_words(string text)
{
    int spaces = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (' ' == text[i])
        {
            spaces++; // Counts spaces
        }
    }

    return spaces + 1;
};

int count_sentences(string text)
{
    int sentences = 0;

    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            sentences++; // Count sentences
        }
    }

    return sentences;
}

int main(void)
{
    string text = get_string("Text: ");

    int letters = count_letters(text);
    int words = count_words(text);
    int sentences = count_sentences(text);

    float L = ((float)letters / (float)words) * 100; // The L in the formula
    float S = ((float)sentences / (float)words) * 100; // The S in the formula

    double g = 0.0588 * L - 0.296 * S - 15.8;
    int index = round(g);

    // Prints the grade
    if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (index >= 16)
    {
        printf("Grade 16+\n");
    }
    else
    {
        printf("Grade %d\n", index);
    }

}

