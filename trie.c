#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define NUM_LETTERS 26

// Node definition
struct Trie {
    int count;
    struct Trie *children[NUM_LETTERS];
};

// Initialize trie node
struct Trie *createNode() 
{
    struct Trie *node = (struct Trie *) malloc(sizeof(struct Trie));
    node->count = 0;
    for (int i = 0; i < NUM_LETTERS; i++) 
    {
        node->children[i] = NULL;
    }
    return node;
}

// Insert word into trie
void insert(struct Trie **ppTrie, char *word) {
    struct Trie *curr = *ppTrie;
    int len = strlen(word);

    for (int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) 
        {
            curr->children[index] = createNode();
        }
        curr = curr->children[index];
    }
    curr->count++;
}

// Count occurrences of a word in the trie
int numberOfOccurances(struct Trie *pTrie, char *word) 
{
    struct Trie *curr = pTrie;
    int len = strlen(word);

    for (int i = 0; i < len; i++) 
    {
        int index = word[i] - 'a';
        if (curr->children[index] == NULL) 
        {
            return 0;
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocate the trie
struct Trie *deallocateTrie(struct Trie *pTrie) 
{
    if (pTrie == NULL) 
    {
        return NULL;
    }

    for (int i = 0; i < NUM_LETTERS; i++) 
    {
        pTrie->children[i] = deallocateTrie(pTrie->children[i]);
    }

    free(pTrie);
    return NULL;
}

int main(void) {
    struct Trie *trie = createNode();

    //read the number of the words in the dictionary
    // parse line by line, and insert each word to the trie data structure
    char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
    for (int i = 0; i < 5; i++) 
    {
        insert(&trie, pWords[i]);
        printf("\t%s : %d\n", pWords[i], numberOfOccurances(trie, pWords[i]));
    }
    trie = deallocateTrie(trie);
    if (trie != NULL)
    {
        printf("There is an error in this program\n");
    }
    return 0;
}