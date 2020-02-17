// Implements a dictionary's functionality

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;

}
node;

// Number of buckets in hash table
const unsigned int N = 729;

// Hash table
node *table[N];

// Total word count
int word_count = 0;

// Returns true if word is in dictionary else false
bool check(const char *word)
{
    int hashnumber;
    hashnumber = hash(word);
    if (table[hashnumber] == NULL)
    {
        return false;
    }
    node *cursor = table[hashnumber];
    while (cursor != NULL)
    {
        if (strcasecmp(cursor->word, word) == 0)
        {
            return true;
        }
        cursor = cursor->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    int firstletter = 0;
    int secondletter = 0;
    int hashnumber;
    char *alphabet = "abcdefghijklmnopqrstuvwxyz'";
    char *alphabetUpper = "ABCDEFGHIJKLMNOPQRSTUVWXYZ'";
    for (int i = 1; i <= 27; i++)
    {
        // Read first letter
        // Hash against alphabet 0-26
        if (word[0] == alphabet[i - 1])
        {
            firstletter = i - 1;
        }
        if (word[0] == alphabetUpper[i - 1])
        {
            firstletter = i - 1;
        }
    }
    for (int i = 1; i <= 27; i++)
    {
        // Read second letter
        // Hash against alphabet 0-26
        if (word[1] == alphabet[i - 1])
        {
            secondletter = i - 1;
        }
        if (word[1] == alphabetUpper[i - 1])
        {
            secondletter = i - 1;
        }
    }
    // do some math
    hashnumber = (firstletter * 27) + secondletter;
    // return number
    return hashnumber;
}

// Loads dictionary into memory, returning true if successful else false
bool load(const char *dictionary)
{
    // Open file
    FILE *file = fopen(dictionary, "r");
    if (file == NULL)
    {
        printf("Could not load dictionary");
        return false;
    }

    char word[LENGTH + 1];
    // fscanf word
    while (fscanf(file, "%s", word) != EOF)
    {
        // Create node for the word
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            printf("Could not load node.");
            return false;
        }
        word_count++;
        strcpy(n->word, word);
        n->next = NULL;
        // Hash word
        int hashnumber;
        hashnumber = hash(word);
        // Insert node into hash table
        if (table[hashnumber] == NULL)
        {
            table[hashnumber] = n;
        }
        else
        {
            n->next = table[hashnumber]->next;
            table[hashnumber]->next = n;
        }
    }
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded else 0 if not yet loaded
unsigned int size(void)
{
    if (word_count == 0)
    {
        return 0;
    }
    else
    {
        return word_count;
    }
}

// Unloads dictionary from memory, returning true if successful else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        node *cursor = table[i];
        node *tmp = cursor;
        while (tmp != NULL)
        {
            cursor = cursor->next;
            free(tmp);
            tmp = cursor;
        }
    }
    return true;
}
