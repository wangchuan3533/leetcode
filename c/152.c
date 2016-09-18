// from 'http://bangbingsyb.blogspot.com/2014/11/leetcode-maximum-product-subarray.html'
#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int maxProduct(int* nums, int numsSize) {
    int i, max, cur_max, cur_min, tmp; 

    if (numsSize <= 0) return 0;
    max = cur_max = cur_min = nums[0];
    for (i = 1; i < numsSize; i++) {
        tmp = cur_max;
        cur_max = MAX(MAX(cur_max * nums[i], cur_min * nums[i]), nums[i]);
        cur_min = MIN(MIN(tmp * nums[i], cur_min * nums[i]), nums[i]);
        max = MAX(cur_max, max);
    }

    return max;
}

int main() {

    int nums[] = {-2, 3, 4, -2, -3};
    int max = maxProduct(nums, 5);
    printf("%d\n", max);
    return 0;
}
