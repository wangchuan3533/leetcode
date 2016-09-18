#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int diff(char** lines1, int count1, char** lines2, int count2) {
    unsigned int *table = (unsigned int *)malloc(sizeof(unsigned int) * (count1 + 1) * (count2 + 1));
    unsigned int x, y, ret;
    unsigned int *stack, offset, type;
#define TABLE(x, y) (table[(y) * (count2 + 1) + (x)])

    for (y = 0; y <= count1; y++) {
        for (x = 0; x <= count2; x++) {
            if (x == 0 || y == 0) {
                TABLE(x, y) = 0;
            } else if (!strcmp(lines1[y - 1], lines2[x - 1])) {
                TABLE(x, y) = TABLE(x - 1, y - 1) + 1;
            } else {
                TABLE(x, y) = MAX(TABLE(x - 1, y), TABLE(x, y - 1));
            }
        }
    }

    ret = TABLE(count1, count2);
    stack = (unsigned int *)malloc(sizeof(unsigned int) * 2 * (count1 + count2 - 2 * ret));
    offset = 0;

    // traceback
    for (x = count2, y = count1; x > 0 || y > 0;) {
        if (x >= 1 && y >= 1 && !strcmp(lines1[y - 1], lines2[x - 1])) {
            stack[offset++] = x - 1;
            stack[offset++] = y - 1;
            stack[offset++] = 0;
            x--;
            y--;
        } else if (x >= 1 && TABLE(x, y) == TABLE(x - 1, y)) {
            stack[offset++] = x - 1;
            stack[offset++] = y - 1;
            stack[offset++] = 1;
            x--;
        } else if (y >= 1 && TABLE(x, y) == TABLE(x, y - 1)) {
            stack[offset++] = x - 1;
            stack[offset++] = y - 1;
            stack[offset++] = 2;
            y--;
        }
    }

    while (offset > 0) {
        type = stack[--offset];
        y = stack[--offset];
        x = stack[--offset];
        
        switch(type) {
        case 0:
            printf("%d,%d\n", y + 1, x + 1);
            break;
        case 1:
            printf("> %s\n", lines2[x]);
            break;
        case 2:
            printf("< %s\n", lines1[y]);
            break;
        }
    }

    free(stack);
    free(table);
#undef TABLE

    return  ret;
}

int main() {
    char *lines1[] = {"hello", "world"},
         *lines2[] = {"hello", "World", "you"};

    int ret = diff(lines1, 2, lines2, 3);
    printf("ret = %d\n", ret);
    return 0;
}
