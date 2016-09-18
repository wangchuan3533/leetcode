#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int minPathSum(int** grid, int gridRowSize, int gridColSize) {
    int ret, left, up, i, j, *buf = (int *)malloc(sizeof(int) * gridColSize);


    // init buf with min
    for (i = 0; i < gridColSize; i++) buf[i] = 0;

    for (i = 0; i < gridRowSize; i++) {
        for (j = 0; j < gridColSize; j++) {
            left = j > 0 ? buf[j - 1] : INT_MAX;
            up = i > 0 ? buf[j] : INT_MAX;
            if (left == INT_MAX && up == INT_MAX) left = 0;
            buf[j] = grid[i][j] + MIN(left, up);
        }
    }
    ret = buf[gridColSize - 1];
    free(buf);
    return ret;
}

int main() {
    int a[] = {1, 1, 1};
    int b[] = {1, 1, 1};
    int c[] = {1, 1, 1};
    int *input[] = {a, b, c};
    int result = minPathSum(input, 3, 3);
    printf("result = %d\n", result);
    return 0;
}
