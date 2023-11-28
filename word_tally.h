/**
 * Header file for word tally functionality.
 */

#ifndef __WORD_TALLY_HEADER__
#define __WORD_TALLY_HEADER__

// Structure to represent a node in the linked list
typedef struct LLNode {
    char *word;            // Word string
    int count;             // Tally count for the word
    struct LLNode *next;   // Pointer to the next node
} LLNode;

// Forward declarations

/**
 * Process a file and tally the words in the appropriate list.
 * @param filename The name of the file to process.
 * @param wordLists An array of linked lists to store word tally information.
 * @param maxLen The maximum length of words to consider.
 * @return 1 if successful, 0 on failure.
 */
int tallyWordsInFile(char *filename, LLNode **wordLists, int maxLen);

/**
 * Print out all of the data in a word list.
 * @param filename The name of the file being processed.
 * @param wordListHeads An array of linked lists containing word tally data.
 * @param maxLen The maximum length of words considered.
 * @return 1 if successful, 0 on failure.
 */
int printData(char *filename, LLNode *wordListHeads[], int maxLen);

/**
 * Print out only the hapax legomena (words that occur only once) in a word list.
 * @param filename The name of the file being processed.
 * @param wordListHeads An array of linked lists containing word tally data.
 * @param maxLen The maximum length of words considered.
 * @param hapaxLength The length of words to consider as hapax legomena.
 * @return 1 if successful, 0 on failure.
 */
int printHapax(char *filename, LLNode *wordListHeads[], int maxLen, int hapaxLength);

/**
 * Delete the contents of all word lists.
 * @param wordListHeads An array of linked lists to be cleaned up.
 * @param maxLen The maximum length of words considered.
 */
void deleteWordLists(LLNode **wordListHeads, int maxLen);

/**
 * Print out the command line help.
 */
void usage();

#endif
