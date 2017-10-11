#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MIN(a, b) ((a) > (b) ? (b) : (a))
int maxArea(int* height, int heightSize)
{
    int i, j, prod;
    int ret = INT_MIN;

    for (i = 0, j = heightSize - 1; i < j;) {
        prod = (j - i) * MIN(height[i], height[j]);
        if (prod > ret) ret = prod;

        if (height[i] < height[j]) {
            i++;
        } else {
            j--;
        }
    }

    return ret;
}

int main()
{
    int arr[] = {1, 3, 2, 5, 25, 24, 5};
    int ret = maxArea(arr, 7);
    printf("ret = %d\n", ret);
    return 0;
}
