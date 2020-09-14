// Implements a dictionary's functionality

#include <stdbool.h>

#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include <strings.h>

#include <ctype.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 26;

// Hash table
node *table[N];

int dictionarySize = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    node *iteration = table[hash(word)];
    while (iteration != NULL)
    {
        char *dicword = iteration -> word;

        if (strcasecmp(dicword, word) == 0)
        {
            return true;
        }

        else
        {
            iteration = iteration -> next;
        }
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    char hashedletter = tolower(word[0]);
    int hashnumber = (int)hashedletter % 26;
    return hashnumber;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    dictionarySize = 0;
    char *currentword = malloc((LENGTH + 1) * sizeof(char));
    node *currentptr = NULL;

    for (int i = 0; i < N; i++)
    {
        table[i] = NULL;
    }

    FILE *dicfile = fopen(dictionary, "r");
    if (dicfile != NULL)
    {
        while (fscanf(dicfile, "%s", currentword) == 1)
        {
            dictionarySize++;
            node *bus = malloc(sizeof(node));
            if (bus != NULL)
            {
                strcpy((bus -> word), currentword);
                bus -> next = NULL;

                if (table[hash(currentword)] == NULL)
                {
                    table[hash(currentword)] = bus;
                }

                else
                {
                    bus -> next = table[hash(currentword)];
                    table[hash(currentword)] = bus;
                }
            }
            else
            {
                free(currentword);
                fclose(dicfile);
                return false;
            }
        }

        free(currentword);
        fclose(dicfile);
        return true;

    }
    return false;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    return dictionarySize;
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    node *cursor = NULL;
    node *temp = NULL;
    for (int i = 0; i < N; i++)
    {
        cursor = table[i];
        while (cursor != NULL)
        {
            temp = cursor;
            cursor = cursor -> next;
            free(temp);
        }

    }
    return true;
}
