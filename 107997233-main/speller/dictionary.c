// Implements a dictionary's functionality
#include <ctype.h>
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
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 26;
int WordCounter = 0;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // create a variable then check the index by using hash and passing in the variable "word"
    int hash_number = hash(word);
    // Create a variable to point to the head of the linked list
    node *position = table[hash_number];
    // Iterate through the list until we reach the end NULL value
    while (position != NULL)
    {
        // Check if the words are in the dictionary
        if (strcasecmp(position->word, word) == 0)
        {
            return true;
        }
        // If not then move the cursors
        position = position->next;
    }
    return false;
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    // return toupper(word[0]) - 'A';
    long total = 0;
    for (int i = 0; i < strlen(word); i++)
    {
        total += tolower(word[i]);
    }
    return total % N;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // Load dictionary to memory
    FILE *DictionaryFile = fopen(dictionary, "r");

    // Check if the file exists and opens otherwise aka NULL
    if (dictionary == NULL)
    {
        return false;
    }

    // Read strings, one at a time from the file
    char str[LENGTH + 1]; // word length plus nul value
    while (fscanf(DictionaryFile, "%s", str) != EOF)
    {
        // Add word to a new node in list
        node *n = malloc(sizeof(node)); // Create a node pointer *n. Size of determines how much memory to allocate
        // check that the memory is actually given to us and has been allocated
        if (n == NULL)
        {
            return false;
        }
        strcpy(n->word, str);

        // Use the hash function
        int hash_number = hash(str);

        // Point n to the first node of the linked list
        /*if (table[hash_number] == NULL)
        {
            // Point to NULL
            n->next = NULL;
        }
        else
        {*/
        // Point to the linked list
        n->next = table[hash_number];
        //}
        table[hash_number] = n;

        WordCounter += 1; // Increment the word counter by 1 if a new word is added
    }
    // Close file and return true
    fclose(DictionaryFile);
    return true; // Because successful
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    return WordCounter; // Global variable for the number of entries in the dictionary
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    for (int i = 0; i < N; i++)
    {
        // Assign a cursor position
        node *position = table[i];
        // Start looping through the list until the end value (NULL) is reached
        while (position)
        {
            // Create a temporary cursor position
            node *tmp = position;
            // Point the position cursor to the next element
            position = position->next;
            // Now free the temporary node
            free(tmp);
            // loop over and over until NULL is reached
        }
    }
    return true;
}