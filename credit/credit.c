#include <cs50.h>
#include <stdio.h>
#include <math.h>

int main(void)
{

    long cnumber = get_long("Number: "); // get the credit card number

    int len = 0;
    long i = cnumber;

    // get the length of the number
    do
    {
        i = i / 10;
        len++;
    }
    while (i > 0);

    // Check the length of the credit number
    if (len != 13 && len != 15 && len != 16)
    {
        printf("INVALID\n");
        return 0;
    }
    // Sum of the Luhn’s Algorithm
    long j = cnumber;
    int s1 = 0;
    int s2 = 0;
    int digit1 = 0;
    int digit2 = 0;
    int m1;
    int m2;
    int total_sum = 0;
    do
    {
        // First digit
        m1 = j % 10;
        j = j / 10;
        s1 = s1 + m1;
        // Second digit
        m2 = j % 10;
        j = j / 10;
        // Multiply by 2
        m2 = m2 * 2;
        digit1 = m2 % 10;
        digit2 = m2 / 10;
        s2 = s2 + digit1 + digit2;
    }
    while (j > 0);

    total_sum = s1 + s2;

    if (total_sum % 10 != 0)
    {
        printf("INVALID\n");
        return 0;
    }
    // Starting digits
    long start = cnumber;
    do
    {
        start = start / 10;
    }
    while (start > 100);
    // Checking starting digits for the card type
    if ((start / 10 == 5) && (0 < start % 10 && start % 10 < 6))
    {
        printf("MASTERCARD\n");
    }
    else if ((start / 10 == 3) && (start % 10 == 4 || start % 10 == 7))
    {
        printf("AMEX\n");
    }
    else if (start / 10 == 4)
    {
        printf("VISA\n");
    }
    else
    {
        printf("INVALID\n");
    }



}