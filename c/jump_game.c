#include <stdio.h>
#define bool int
#define true 1
#define false 0

bool canJump(int* nums, int numsSize)
{
    int i, maxIndex = 0;

    for (i = 0; i < numsSize; i++) {
        if (i > maxIndex || maxIndex >= (numsSize - 1)) {
            break;
        }
        if (i + nums[i] > maxIndex) {
            maxIndex = i + nums[i];
        }
    }
    return maxIndex >= (numsSize - 1);
}

int main()
{
    int arr[] = {
        2, 0, 6, 9, 8, 4, 5, 0, 8, 9, 1, 2, 9, 6, 8, 8, 0,
        6, 3, 1, 2, 2, 1, 2, 6, 5, 3, 1, 2, 2, 6, 4, 2, 4,
        3, 0, 0, 0, 3, 8, 2, 4, 0, 1, 2, 0, 1, 4, 6, 5, 8,
        0, 7, 9, 3, 4, 6, 6, 5, 8, 9, 3, 4, 3, 7, 0, 4, 9,
        0, 9, 8, 4, 3, 0, 7, 7, 1, 9, 1, 9, 4, 9, 0, 1, 9,
        5, 7, 7, 1, 5, 8, 2, 8, 2, 6, 8, 2, 2, 7, 5, 1, 7,
        9, 6
    };

    bool ret = canJump(arr, sizeof(arr) / sizeof(int));
    printf("ret = %d\n", ret);
    return 0;
}
