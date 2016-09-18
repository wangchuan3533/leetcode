#include <stdio.h>
#include <stdlib.h>

typedef int bool;
#define true 1
#define false 0

bool word_equal(char *a, char *b)
{
    while (1) {
        if (*a == *b) {
            if (*a == ' ' || *a == '\0') {
                return true;
            } else {
                a++;
                b++;
            }
        } else {
            if ((*a == ' ' || *a == '\0') && (*b == ' ' || *b == '\0')) {
                return true;
            } else {
                //printf("a=%c, b=%c\n", *a, *b);
                return false;
            }
        }
    }
}

bool wordPattern(char* pattern, char* str)
{
    int i, j, k, index;
    char *table[26];

    // init table
    for (i = 0; i < 26; i++) table[i] = NULL;

    for (i = 0, j = 0; pattern[i] != '\0' && str[j] != '\0'; i++) {
        //printf("patten %c\n", pattern[i]);
        index = pattern[i] - 'a';
        if (table[index]) {
            if (!word_equal(table[index], str + j)) {
                return false;
            }
        } else {
            for (k = 0; k < 26; k++) {
                if (k != index && table[k] && word_equal(table[k], str + j)) {
                    return false;
                }
            }
            table[index] = str + j;
        }
        while (str[j] != ' ' && str[j] != '\0') j++;
        if (str[j] == ' ') j++;
    }

    if (pattern[i] == '\0' && str[j] == '\0') return true;
    return false;
}

int main()
{
    char *pattern = "abba", *str = "dog dog dog dog";
    int ret = wordPattern(pattern, str);
    //printf("ret = %d\n", ret);
    return 0;
}
