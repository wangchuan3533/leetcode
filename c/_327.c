#include <stdio.h>
#include <stdlib.h>
int countRangeSum(int* nums, int numsSize, int lower, int upper) {
    unsigned int i, j;
    long sum, result = 0;

    for (i = 0; i < numsSize; i++) {
        for (j = i, sum = 0; j < numsSize; j++) {
            sum += nums[j];
            if (sum >= lower && sum <= upper) result++;
        }
    }
    return result;
}

int main() {
    int nums[] = {-2, 5, -1};
    int result = countRangeSum(nums, 3, -2, 2);
    printf("result=%d\n", result);
    return 0;
}
