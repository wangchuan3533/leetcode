#include <stdio.h>
#include <stdlib.h>

int lengthOfLIS(int* nums, int numsSize) {
    int i, j, *a = (int *)malloc(sizeof(int) * numsSize);
    int max = 0;

    for (i = 0; i < numsSize; i++) {
        for (a[i] = 1, j = 0; j < i; j++) {
            if (nums[j] < nums[i] && a[j] + 1 > a[i]) {
                a[i] = a[j] + 1;
            }
        }
        if (a[i] > max) max = a[i];
    }
    free(a);
    return max;
}

int main() {
    int nums[] = {3,5,6,2,5,4,19,5,6,7,12};

    int ret = lengthOfLIS(nums, sizeof(nums) / sizeof(int));
    printf("ret=%d\n", ret);
    return 0;
}
