#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned int word2int(const char *word, unsigned int *len)
{
    unsigned bits = 0;
    int i;
    for (i = 0; word[i] != 0; i++) {
        bits |= (1u << (word[i] - 'a'));
    }

    *len = i;
    return bits;
}

int maxProduct(char** words, int wordsSize)
{
    unsigned int *words_bits = (unsigned int *)malloc(sizeof(unsigned int) * wordsSize);
    unsigned int *words_len = (unsigned int *)malloc(sizeof(unsigned int) * wordsSize);
    int i, j, max, prod;

    for (i = 0; i < wordsSize; i++) {
        words_bits[i] = word2int(words[i], &words_len[i]);
    }

    for (i = 0, max = 0; i < wordsSize; i++) {
        for (j = i + 1; j < wordsSize; j++) {
            if (words_bits[i] & words_bits[j]) continue;
            prod = words_len[i] * words_len[j];
            if (prod > max) max = prod;
        }
    }

    free(words_bits);
    free(words_len);
    return max;
}

int main()
{
    //const char *word = "abcw";
    //unsigned int bits = word2int(word);
    //printf("bits = %#x\n", bits);

    char *words[] = {"abcw", "baz", "foo", "bar", "xtfn", "abcdef"};
    int ret = maxProduct(words, 6);
    printf("ret = %d\n", ret);

    return 0;
}
