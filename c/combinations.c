#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void calc(int *prefix, int prefix_size, int k, int n, int *returnSize, int **output)
{
    int i;

    if (prefix_size == k) {
        output[*returnSize] = (int *)malloc(k * sizeof(int));
        memcpy(output[(*returnSize)++], prefix, k * sizeof(int));
        return;
    }

    for (i = (prefix_size > 0 ? prefix[prefix_size - 1] : 0) + 1; i <= n; i++) {
        prefix[prefix_size] = i;
        calc(prefix, prefix_size + 1, k, n, returnSize, output);
    }
}

/**
 * Return an array of arrays of size *returnSize.
 * The sizes of the arrays are returned as *columnSizes array.
 * Note: Both returned array and *columnSizes array must be malloced, assume caller calls free().
 */


int** combine(int n, int k, int** columnSizes, int* returnSize)
{
    int i, output_size, *prefix, **output;

    for (i = 0, output_size = 1; i < k; i++) {
        output_size *= n - i;
        output_size /= 1 + i;
    }

    *columnSizes = (int *)malloc(output_size * sizeof(int));
    output = (int **)malloc(output_size * sizeof(int *));
    prefix = (int *)malloc(sizeof(int) * k);

    for (i = 0; i < output_size; i++) {
        (*columnSizes)[i] = k;
    }

    *returnSize = 0;
    calc(prefix, 0, k, n, returnSize, output);
    free(prefix);

    return output;
}

int main()
{
    int i, j, returnSize, *columnsSizes, **output;

    output = combine(4, 2, &columnsSizes, &returnSize);

    for (i = 0; i < returnSize; i++) {
        printf("[");
        for (j = 0; j < columnsSizes[i]; j++) {
            printf("%d,", output[i][j]);
        }
        free(output[i]);
        printf("]\n");
    }

    free(columnsSizes);
    free(output);
    return 0;
}
