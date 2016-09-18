#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

#define MIN(a, b) ((a) < (b) ? (a) : (b))
int tsp(int a[4][4], int n) {
    unsigned int i, j, k, s, ret, num_combinations;
    int *table;

    num_combinations = 1 << n;
    table = (int *)malloc(sizeof(int) * n * num_combinations);

#define TABLE(row, col) (table[(row) * num_combinations + (col)])
    // init with int_max
    for (i = 0; i < n; i++) {
        for (s = 0; s < num_combinations; s++) {
            TABLE(i, s) = INT_MAX;
        }
    }

    // when |s| == 2
    for (i = 1; i < n; i++) {
        s = 1 | (1 << i);
        TABLE(i, s) = a[0][i];
    }

    // when |s| > 2
    for (s = 1; s < num_combinations; s++) {
        if (!(s & (1 << 0))) continue;
        for (i = 1; i < n; i++) {
            if (!(s & (1 << i))) continue;
            for (j = 0; (1 << j) <= s; j++) {
                if (j == 0 || j == i) continue;
                if (!(s & (1 << j))) continue;
                k = s & ~(1 << i);
                TABLE(i, s) = MIN(TABLE(i, s), TABLE(j, k) + a[j][i]);
                printf("i = %u, s = %u, j = %u, k = %u, T = %u\n", i, s, j, k, TABLE(i, s));
            }
        }
    }

    // find the result
    ret = INT_MAX;
    s = num_combinations - 1;
    for (i = 1; i < n; i++) {
        if (ret > TABLE(i, s) + a[i][0]) {
            ret = TABLE(i, s) + a[i][0];
        }
    }
#undef TABLE
    free(table);
    return ret;
}

int main() {
    int ret, a[][4] = {
        {0, 3, 6, 7},
        {5, 0, 2, 3},
        {6, 4, 0, 2},
        {3, 7, 5, 0}
    };

    ret = tsp(a, 4);
    printf("result=%d\n", ret);

    return 0;
}
