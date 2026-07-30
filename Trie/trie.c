#include "trie.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

Trie* createTrie(const bool case_sensitive) {
    Trie* trie = (Trie*)malloc(sizeof(Trie));
    if (!trie) {
        perror("[trie.c][createTrie()] ERROR: Failed to allocate memory for Trie");
        return NULL;
    }

    for (int i = 0; i < MAX_CHAR; ++i)
        trie->child_nodes[i] = NULL;

    trie->nwords = 0;
    trie->case_sensitive = case_sensitive;

    return trie;
}

TrieNode* createTrieNode(void) {
    TrieNode* trie_node = (TrieNode*)malloc(sizeof(TrieNode));
    if (!trie_node) {
        perror("[trie.c][createTrieNode()] ERROR: Failed to allocate memory for TrieNode");
        return NULL;
    }

    for (int i = 0; i < MAX_CHAR; ++i) {
        trie_node->child_nodes[i] = NULL;
    }
    trie_node->word = false;

    return trie_node;
}

void addWordTrie(Trie* trie, char* word, const unsigned int n) {
    if (trie == NULL) {
        fprintf(stderr, "[trie.c][addWordTrie()] WARNING: Trie object doesn't exist.\n");
        return;
    }

    if (word == NULL || n == 0) {
        fprintf(stderr, "[trie.c][addWordTrie()] WARNING: Can't add word to Trie. Word is equal to NULL or word size (`n`) is equal to 0.\n");
        return;
    }

    // Root node
    unsigned char curr_char = (unsigned char)word[0];
    if(trie->child_nodes[curr_char] == NULL){
        TrieNode* new_node = createTrieNode();
        if(!new_node) return;
        trie->child_nodes[curr_char] = new_node;
    }
   
    TrieNode* curr = trie->child_nodes[curr_char];
    for(unsigned i = 1; i < n; ++i){
        curr_char = (unsigned char) word[i];
        if(!curr->child_nodes[curr_char]){
            TrieNode* new_node = createTrieNode();
            if(!new_node) return;
            curr->child_nodes[curr_char] = new_node;
        }
        curr = curr->child_nodes[curr_char];
    }

    if(!curr->word){
        curr->word = true;
        trie->nwords += 1;
    }
    return;
}

bool wordExistsTrie(Trie* trie, char* word, const unsigned int n) {
    if (trie == NULL) {
        fprintf(stderr, "[trie.c][patternExistsTrie()] WARNING: Trie object doesn't exist.\n");
        return false;
    }

    if (word == NULL || n == 0) {
        fprintf(stderr, "[trie.c][patternExistsTrie()] WARNING: Invalid search input. Word is NULL or length is equal to 0.\n");
        return false;
    }

    unsigned char curr_char = (unsigned char) word[0];
    TrieNode* curr = trie->child_nodes[curr_char];
    if(!curr) return false;

    for(unsigned i = 1; i < n; ++i){
        curr_char = (unsigned char) word[i];
        curr = curr->child_nodes[curr_char];
        if(!curr) return false;
    }

    return curr->word;
}

bool prefixExistsTrie(Trie* trie, char* prefix, const unsigned int n){
    if (trie == NULL) {
        fprintf(stderr, "[trie.c][prefixExistsTrie()] WARNING: Trie object doesn't exist.\n");
        return false;
    }

    if (prefix == NULL || n == 0) {
        fprintf(stderr, "[trie.c][prefixExistsTrie()] WARNING: Invalid search input. Word is NULL or length is equal to 0.\n");
        return false;
    }

    unsigned char curr_char = (unsigned char) prefix[0];
    TrieNode* curr = trie->child_nodes[curr_char];
    if(!curr) return false;

    for(unsigned i = 1; i < n; ++i){
        curr_char = (unsigned char) prefix[i];
        curr = curr->child_nodes[curr_char];
        if(!curr) return false;
    }

    return true;
}

void freeTrieNode(TrieNode* trie_node) {
    if (trie_node == NULL) {
        fprintf(stderr, "[trie.c][freeTrieNode()] WARNING: TrieNode is equal to NULL.\n");
        return;
    }

    for(int i = 0; i < MAX_CHAR; ++i){
        if(!trie_node->child_nodes[i]) 
            continue;

        freeTrieNode(trie_node->child_nodes[i]);
    }
    free(trie_node);
}

void freeTrie(Trie* trie) {
    if (trie == NULL) {
        fprintf(stderr, "[trie.c][freeTrie()] WARNING: Trie object doesn't exist.\n");
        return;
    }

    for(int i = 0; i < MAX_CHAR; ++i){
        if(!trie->child_nodes[i]) 
            continue;

        freeTrieNode(trie->child_nodes[i]);
    }

    free(trie);
}