#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie structure
struct Trie
{
    int count;
    struct Trie* children[26];
    struct Trie* next;	
};


// Initializes a trie structure
struct Trie *createTrie()
{
    struct Trie *myTrie = (struct Trie*) malloc (sizeof(struct Trie));
    myTrie -> count = 0;
    myTrie -> next = NULL;

    for (int i= 0 ; i < 26 ; i++)
    {
        myTrie -> children[i] = NULL;
    }

    return myTrie;
}

// Inserts the word to the trie structure
void insert(struct Trie *pTrie, char *word)
{  
    int index, i;
    struct Trie *temp = pTrie;

    for (i = 0 ; i < strlen(word) ; i++)
    {
        index = word[i] - 'a';

        if (!temp -> children[index]){
            temp-> children[index] = createTrie();
        }
        temp = temp -> children[index];
    }
    temp->count++;
}

// computes the number of occurances of the word
int numberOfOccurances(struct Trie *pTrie, char *word)
{
    if (!pTrie) 
        return 0;
	if (*word == '\0') 
        return pTrie->count;

	return numberOfOccurances(pTrie -> children[*word - 'a'], word + 1);
}

// deallocate the trie structure
struct Trie *deallocateTrie(struct Trie *pTrie)
{
    // In case the Tree is empty
    if (!pTrie);
        return NULL;

    for (int i = 0 ; i < 26 ; i++)
    {
        deallocateTrie(pTrie -> children[i]);
    }
    free(pTrie);
    return pTrie;    
}

// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
    FILE* input = fopen(filename, "r");
    if (input == NULL)
        return -1;
    int words;
    char word[50]; 
    fscanf (input, "%d\n", &words);

    for (int i = 0 ; i < words ; i++)
    {
        fscanf (input, "%s\n", word);
        pInWords[i] = (char*) malloc ((strlen(word) + 1) *sizeof(char));
        if (pInWords[i] == NULL)
            return -1;
        strcpy (pInWords[i], word);
    }

    fclose(input);

    return words;
}

int main(void)
{
	char *inWords[256];
	
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary-1.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurances(pTrie, pWords[i]));
	}
	pTrie = deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}