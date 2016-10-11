typedef int bool;
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
bool isInterleave(char* s1, char* s2, char* s3)
{
    bool ret;
    size_t width = strlen(s1) + 1, height = strlen(s2) + 1, total = width * height;
    if (width + height - 2 != strlen(s3)) return 0;
    char *table = (char *)malloc(sizeof(char) * width * height);
    memset(table, 0, sizeof(char) * total);

    int i, count = 0;
    for (table[0] = 1, i = 1; i < total; i++) {
        size_t x = i % width, y = i / width;
        if ((x > 0 && table[i - 1] > 0 && s1[x - 1] == s3[x + y - 1]) || (y > 0 && table[i - width] > 0 && s2[y - 1] == s3[x + y - 1])) {
            table[i] = 1;
            count++;
        }
        if ((count + 1) * width < i) {
            break;
        }
    }

    ret = table[total - 1];
    free(table);
    return ret;
}


int main()
{
    char *s1 = "aabcc", *s2 = "dbbca", *s3 = "aadbbcbcac", *s4 = "aadbbbaccc";

    char *s5 = "bbbbbabbbbabaababaaaabbababbaaabbabbaaabaaaaababbbababbbbbabbbbababbabaabababbbaabababababbbaaababaa";
    char *s6 = "babaaaabbababbbabbbbaabaabbaabbbbaabaaabaababaaaabaaabbaaabaaaabaabaabbbbbbbbbbbabaaabbababbabbabaab";
    char *s7 = "babbbabbbaaabbababbbbababaabbabaabaaabbbbabbbaaabbbaaaaabbbbaabbaaabababbaaaaaabababbababaababbababbbababbbbaaaabaabbabbaaaaabbabbaaaabbbaabaaabaababaababbaaabbbbbabbbbaabbabaabbbbabaaabbababbabbabbab";

    bool ret1 = isInterleave(s1, s2, s3);
    bool ret2 = isInterleave(s1, s2, s4);
    bool ret3 = isInterleave(s5, s6, s7);

    printf("ret1 = %d, ret2 = %d ret3 = %d\n", ret1, ret2, ret3);
}
