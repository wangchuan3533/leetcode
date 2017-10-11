#include <stdio.h>
#include <stdlib.h>
int lengthOfLongestSubstring(char* s)
{
    int max = 0;
    char *start, *cur;
    char count[256] = {0};

    if (s == NULL) return 0;
    for (start = cur = s; *cur != 0;) {
        if (count[*cur]) {
            while (count[*cur] > 0) {
                count[*start++]--;
            }
        }
        if (cur - start + 1 > max) max = cur - start + 1;
        count[*cur] += 1;
        cur++;
    }

    return max;
    
}

int main()
{
    //char *str = "abcabcbb";
    //char *str = "bbbbb";
    char *str = "pwwkew";
    int max = lengthOfLongestSubstring(str);
    printf("ret = %d\n", max);
    return 0;
}
