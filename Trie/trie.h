#ifndef TRIE_H
#define TRIE_H

#include <stdbool.h>

#define MAX_CHAR 256

typedef struct TrieNode {
    struct TrieNode* child_nodes[MAX_CHAR];
    char letter;
    bool word;
} TrieNode;

typedef struct Trie {
    TrieNode* child_nodes[MAX_CHAR];
    unsigned int nwords;
    bool case_sensitive;
} Trie;

Trie* createTrie(const bool case_sensitive);
void addWordTrie(Trie* trie, char* word, const unsigned int n);
bool wordExistsTrie(Trie* trie, char* word, const unsigned int n);
bool prefixExistsTrie(Trie* trie, char* prefix, const unsigned int n);
void freeTrie(Trie* trie);

#endif
