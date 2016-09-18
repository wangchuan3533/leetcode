#include <stdio.h>
#include <stdlib.h>

int findPivot(int *nums, int numsSize)
{
    int start, end, mid;
    for (start = 0, end = numsSize - 1; end > start;) {
        mid = (start + end) / 2;
        if (mid == start) {
            return mid;
        } else if (nums[mid] > nums[end]) {
            start = mid;
        } else {
            end = mid;
        }
    }

    return start;
}

int binary_search(int *nums, int start, int end, int target) {
    int mid;

    while (start < end) {
        mid = (start + end) / 2;
        if (mid == start) break;
        if (nums[mid] > target) {
            end = mid; 
        } else {
            start = mid;
        }
    }

    if (nums[start] == target) return start;
    if (nums[end] == target) return end;
    return -1;
}

int search(int* nums, int numsSize, int target)
{
    int pivot, ret;

    if (numsSize < 1) return -1;
    pivot = findPivot(nums, numsSize);

    if (pivot >= 0) {
        ret = binary_search(nums, 0, pivot, target);
        if (ret >= 0) return ret;
    }

    if (pivot + 2 <= numsSize) {
        ret = binary_search(nums, pivot + 1, numsSize - 1, target);
        if (ret >= 0) return ret;
    }

    return -1;
}


int main()
{
    int arr[] = {1};
    int ret = search(arr, 1, 0);

    printf("ret = %d\n", ret);
    return 0;
}
