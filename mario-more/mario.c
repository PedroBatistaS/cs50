#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height = 0;
    int space = 0;
    int row = 0;
    int hash = 0;
    do
    {
        height = get_int("Height: "); // ask for the heigth
    }
    while (1 > height || height > 8);

    do
    {

        space = height - (row + 1); // prints the spaces
        for (int i = 0; i < space; i++)
        {
            printf(" ");
        }

        hash = row + 1; // prints the first pyramid
        for (int j = 0; j < hash; j++)
        {
            printf("#");
        }

        printf("  ");

        for (int k = 0; k < hash; k++)
        {
            // prints the second pyramid
            printf("#");
        }

        printf("\n");
        row++;

    }
    while (height > row);
}

