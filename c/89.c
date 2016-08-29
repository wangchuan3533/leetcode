#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* grayCode(int n, int* returnSize)
{
    int i, *result;

    *returnSize = 1u << n;
    result = (int *)malloc(sizeof(int) * (*returnSize));
    
    for (i = 0; i < *returnSize; i++) {
        result[i] = i ^ (i >> 1);
    }

    return result;
}

int main()
{
    int i, returnSize = 0;
    int *result = grayCode(2, &returnSize);

    for (i = 0; i < returnSize; i++) {
        printf("%d\n", result[i]);
    }
}
