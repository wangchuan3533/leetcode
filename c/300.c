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

int binary_search(int *arr, int len, int val)
{
    int start, end, mid;

    if (len == 0) return 0;

    for (start = 0, end = len; start + 1 < end;) {
        mid = (start + end) / 2;
        if (arr[mid] == val) {
            return mid;
        } else if (arr[mid] > val) {
            end = mid;
        } else {
            start = mid;
        }
    }

    if (val > arr[start]) return end;
    return start;
}

int lengthOfLISBS(int *nums, int numsSize)
{
    int i, j, len, *dp = (int *)malloc(numsSize * sizeof(int));

    for (i = 0, len = 0; i < numsSize; i++) {
        j = binary_search(dp, len, nums[i]);
        dp[j] = nums[i];
        if (j == len) len++;
    }
    free(dp);
    return len;
}

int main() {
    int nums[] = {3,5,6,2,5,4,19,5,6,7,12};

    int ret = lengthOfLIS(nums, sizeof(nums) / sizeof(int));
    printf("ret=%d\n", ret);

    int arr[] = {1, 3, 5, 6, 8, 9};
    int ret2 = binary_search(arr, 6, 5);
    printf("ret2=%d\n", ret2);
    int ret3 = binary_search(arr, 6, 7);
    printf("ret3=%d\n", ret3);

    int ret4 = lengthOfLISBS(nums, sizeof(nums) / sizeof(int));
    printf("ret4=%d\n", ret4);

    return 0;
}
