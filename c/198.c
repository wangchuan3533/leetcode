#include <stdio.h>
#include <stdlib.h>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
int rob(int* nums, int numsSize) {
    int ret = 0, i, a, b, *m = (int *)malloc(numsSize * sizeof(int));

    for (i = 0; i < numsSize; i++) {
        a = i >= 2 ? m[i - 2] : 0;
        b = i >= 1 ? m[i - 1] : 0;
        m[i] = MAX(a + nums[i], b);
    }

    ret = m[numsSize - 1];
    free(m);

    return ret;
}

int main() {
    int nums[] = {1, 2, 3, 4};
    int ret = rob(nums, 4);
    printf("ret=%d\n", ret);
    return 0;
}
