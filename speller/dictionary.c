// Implements a dictionary's functionality

#include <stdbool.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 50000;

// Hash table
node *table[N];

// Dictionary counter
int c = 0;

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    int hashCode = hash(word);
    node *cursor = table[hashCode];

    for (node *tmp = cursor; tmp != NULL; tmp = tmp->next)
    {
        if (strcasecmp(tmp->word, word) == 0)
        {
            return true;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int hash = 0;

    for (int i = 0; i < strlen(word); i++)
    {
        hash += tolower(word[i]);
        hash = (hash * tolower(word[i])) % N;
    }
    return hash;

}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    FILE  *file = fopen(dictionary, "r");

    if (file == NULL)
    {
        fprintf(stderr, "Couldn't open the file");
        return false;
    }

    char wl[LENGTH + 1];

    while (fscanf(file, "%s", wl) != EOF)
    {
        c++;
        node *newnode = malloc(sizeof(node));

        if (newnode == NULL)
        {
            return 1;
        }
        strcpy(newnode->word, wl);
        newnode->next = NULL;
        int i = hash(wl);

        if (table[i] == NULL)
        {
            table[i] = newnode;
        }
        else
        {
            newnode->next = table[i];
            table[i] = newnode;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return c;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];

        while (cursor != NULL)
        {
            node *tmp = cursor;
            cursor = cursor->next;
            free(tmp);
        }
    }
    return true;
}
