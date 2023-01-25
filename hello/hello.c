#include <stdio.h>
#include <cs50.h>
int main(void)
{
    string name = get_string("What's your name?\n"); // ask for the name
    printf("hello, %s\n", name); // prints the name
}