#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

static int cmp(const void *a, const void *b)
{
    int x = *((int *)a), y = *((int *)b);
    if (x > y) return 1;
    if (x < y) return -1;
    return 0;
}

int threeSumClosest(int* nums, int numsSize, int target)
{
    int i, begin, end, min, diff, result, sum;
    qsort(nums, numsSize, sizeof(int), cmp);

    min = INT_MAX;
    for (i = 0; i < numsSize; i++) {
        for (begin = i + 1, end = numsSize - 1; begin < end;) {
            sum = nums[i] + nums[begin] + nums[end];
            diff = abs(sum - target);
            if (diff == 0) return sum;
            if (diff < min) {
                min = diff;
                result = sum;
            }

            if (sum > target) {
                end--;
            } else {
                begin++;
            }
            
        }
    }
    return result;
}

int main()
{
    int nums[] = {1, 1, 1, 0};
    int target = -100;
    int ret = threeSumClosest(nums, 4, target);
    printf("ret = %d\n", ret);
    return 0;
}
