#include "../trie.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <assert.h>
#include <time.h>

void testCreateAndFree(void);
void testInsertAndSearch(void);
void testEdgeCases(void);

int main(){
    testCreateAndFree();
    puts("Create and Free are working properly!");

    testInsertAndSearch();
    puts("Insert and Search are working properly!");

    testEdgeCases();
    puts("Edge cases are being treated accordingly!");

    return 0;
}

void testCreateAndFree(void){
    Trie *trie = createTrie(true);
    assert(trie != NULL);
    assert(trie->nwords == 0);
    assert(trie->case_sensitive == true);

    freeTrie(trie);
}

void testInsertAndSearch(void){
    Trie *trie = createTrie(true);

    char *word1 = "carro";
    char *word2 = "casa";
    char *word3 = "casamento";
    
    addWordTrie(trie, word1, strlen(word1));
    addWordTrie(trie, word2, strlen(word2));
    addWordTrie(trie, word3, strlen(word3));

    // Search for existing words
    assert(wordExistsTrie(trie, word1, strlen(word1)) == true);
    assert(wordExistsTrie(trie, word2, strlen(word2)) == true);
    assert(wordExistsTrie(trie, word3, strlen(word3)) == true);

    // Search for prefixes
    char *prefix1 = "cas";
    char *prefix2 = "car";

    assert(wordExistsTrie(trie, prefix1, strlen(prefix1)) == false);
    assert(wordExistsTrie(trie, prefix2, strlen(prefix2)) == false);

    assert(prefixExistsTrie(trie, prefix1, strlen(prefix1)) == true);
    assert(prefixExistsTrie(trie, prefix2, strlen(prefix2)) == true);

    // Nonexistent words
    char *nonexistent = "caminhao";
    assert(wordExistsTrie(trie, nonexistent, strlen(nonexistent)) == false);

    // Nonexistent prefixes
    char *nonexistent_prefix1 = "cam";
    char *nonexistent_prefix2 = "rro";
    assert(prefixExistsTrie(trie, nonexistent_prefix1, strlen(nonexistent_prefix1)) == false);
    assert(prefixExistsTrie(trie, nonexistent_prefix2, strlen(nonexistent_prefix2)) == false);

    freeTrie(trie);
}

void testEdgeCases(void){
    Trie* trie = createTrie(false);

    // Invalid arguments
    addWordTrie(NULL, "test", 4);
    addWordTrie(trie, NULL, 4);
    addWordTrie(trie, "test", 0);

    assert(wordExistsTrie(NULL, "test", 4) == false);
    assert(wordExistsTrie(trie, NULL, 4) == false);
    assert(wordExistsTrie(trie, "test", 0) == false);

    // Inserts same word twice
    char *word = "caminhao";
    addWordTrie(trie, word, strlen(word));
    addWordTrie(trie, word, strlen(word));

    assert(trie->nwords == 1);

    assert(wordExistsTrie(trie, word, strlen(word)) == true);

    freeTrie(trie);
}
