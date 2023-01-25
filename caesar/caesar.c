#include <cs50.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>




int main(int argc, string argv[])
{
    // Check the arguments
    if (argc == 2)
    {
        for (int j = 0; j < strlen(argv[1]); j++)
        {
            if (isdigit(argv[1][j]) == false)
            {
                printf("Usage: ./caesar key\n"); // Checks if it is a number
                return 1;
            }
        }

        int key = atoi(argv[1]); // Save the key
        string text = get_string("plaintext: ");

        printf("ciphertext: ");

        for (int i = 0; i < strlen(text); i++)
        {
            // Prints the correct character
            if (isalpha(text[i]))
            {
                // For lowercase
                if ('a' <= text[i]  &&  text[i] <= 'z')
                {
                    printf("%c", (((text[i] - 'a') + key) % 26) + 'a'); // The difference is the index and we add again the value
                }
                // For Uppercase
                else if ('A' <= text[i]  &&  text[i] <= 'Z')
                {
                    printf("%c", (((text[i] - 'A') + key) % 26) + 'A'); // The difference is the index and we add again the value
                }
            }
            else
            {
                // Prints if it is not a letter
                printf("%c", text[i]);
            }
        }


        printf("\n");
        return 0; // Finish
    }
    else
    {
        printf("Usage: ./caesar key\n"); // The number of arguments is different of 2
        return 1;
    }

}