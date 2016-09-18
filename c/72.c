#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minDistance(char* word1, char* word2) {
    unsigned int height = strlen(word1), width = strlen(word2), *table = (unsigned int *)malloc(sizeof(unsigned int) * (width + 1) * (height + 1));
    unsigned int x, y, ret, cost;
#define TABLE(x, y) (table[(y) * (width + 1) + (x)])
    for (y = 0; y <= height; y++) TABLE(0, y) = y;
    for (x = 0; x <= width; x++) TABLE(x, 0) = x;

    for (y = 1; y <= height; y++) {
        for (x = 1; x <= width; x++) {
            cost = word1[y - 1] == word2[x - 1] ? 0 : 1;
            TABLE(x, y) = MIN(MIN(TABLE(x - 1, y), TABLE(x, y - 1)) + 1, TABLE(x - 1, y - 1) + cost);
        }
    }

    ret = TABLE(width, height);
    free(table);
#undef TABLE

    return  ret;
}

int main() {
    char *word1 = "", *word2 = "a";

    int ret = minDistance(word1, word2);
    printf("ret = %d\n", ret);
    return 0;
}
