#include <stdio.h>
#include <stdlib.h>

int numTrees(int n)
{
    int i, j, ret, *table = (int *)malloc(sizeof(int) * (n + 1));
    table[0] = 1;
    for (i = 1; i <= n; i++) {
        table[i] = 0;
        for (j = 0; j < i; j++) {
            table[i] += table[j] * table[i - j - 1];
        }
        //printf("i = %d, v = %d\n", i, table[i]);
    }

    ret = table[n];
    free(table);
    return ret;
}

int main()
{
    int v = numTrees(3);
    return 0;
}
