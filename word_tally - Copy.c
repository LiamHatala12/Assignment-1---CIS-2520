// word_tally.c

#include <stdio.h>
#include <stdlib.h> // for malloc(), free()
#include <string.h>

#include "word_extractor.h"
#include "word_tally.h"

// Forward declarations
static int updateWordInTallyList(LLNode **wordLists, int maxLen, char *word);

// Initialize the word tally lists to NULL
void initWordTallyLists(LLNode **wordLists, int maxLen) {
    for (int i = 0; i < maxLen; i++) {
        wordLists[i] = NULL;
    }
}

/*
 * Process the file and tally the words in the appropriate list.
 */
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen) {
    struct WordExtractor *wordExtractor = NULL;
    char *aWord = NULL;

    // Create the extractor and open the file
    wordExtractor = weCreateExtractor(filename, maxLen);

    if (wordExtractor == NULL) {
        fprintf(stderr, "Failed creating extractor for '%s'\n", filename);
        return 0;
    }

    // Initialize wordLists to NULL (Added this function)
    initWordTallyLists(wordLists, maxLen);

    int totalWordCount = 0;

    while (weHasMoreWords(wordExtractor)) {
        aWord = weGetNextWord(wordExtractor);
        totalWordCount++;

        // Update the word tally list
        updateWordInTallyList(wordLists, maxLen, aWord);
    }

    printf("Total word count %d\n", totalWordCount);

    // Close the file when done
    weDeleteExtractor(wordExtractor);

    return 1;
}

/*
 * Update the tally in the list or add the word to the list.
 */
static int updateWordInTallyList(LLNode **wordListHeads, int maxLen, char *word) {
    // Calculate a hash value for the word
    int hash = 0;
    for (int i = 0; word[i] != '\0'; i++) {
        hash += word[i];
    }
    hash %= maxLen;

    // Traverse the linked list at the calculated index
    LLNode *current = wordListHeads[hash];
    while (current != NULL) {
        if (strcmp(current->word, word) == 0) {
            // Word is already in the list, update tally
            current->count++;
            return 1; // Success
        }
        current = current->next;
    }

    // If the word is not in the list, create a new node and add it
    LLNode *newNode = (LLNode *)malloc(sizeof(LLNode));
    if (newNode == NULL) {
        fprintf(stderr, "Memory allocation error\n");
        return 0; // Error
    }
    newNode->word = strdup(word);
    newNode->count = 1;
    newNode->next = wordListHeads[hash];
    wordListHeads[hash] = newNode;

    return 1; // Success
}
