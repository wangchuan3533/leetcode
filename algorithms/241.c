#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calc(int a, int b, int op)
{
    switch (op) {
    case '+':
        return a + b;
    case '-':
        return a - b;
    case '*':
        return a * b;
    }

    fprintf(stderr, "invalid op %c\n", op);
    exit(1);
    return 0;
}

struct vector {
    int *data;
    int length;
};

struct vector *create_vector(int length)
{
    struct vector *ret = (struct vector *)malloc(sizeof(struct vector));
    if (length > 0) ret->data = (int *)malloc(sizeof(int) * length);
    ret->length = length;
    return ret;
}

void release_vector(struct vector *v)
{
    if (v && v->length > 0) free(v->data);
    free(v);
}

void print_vector(struct vector *v)
{
    int i;
    printf("[");
    for (i = 0; i < v->length; i++) {
        printf("%d%s", v->data[i], ((i < v->length - 1) ? ", " : ""));
    }
    printf("]\n");
}

struct vector *mul(struct vector *v1, struct vector *v2, int op)
{
    int i, j, k;
    struct vector *ret = (struct vector *)malloc(sizeof(struct vector));

    ret->length = v1->length * v2->length;
    ret->data = (int *)malloc(sizeof(int) * ret->length);

    for (i = 0; i < v1->length; i++) {
        for (j = 0; j < v2->length; j++) {
            k = j + i * v2->length;
            ret->data[k] = calc(v1->data[i], v2->data[j], op);
        }
    }

    return ret;
}

struct vector *concat(struct vector *v1, struct vector *v2)
{
    int i;
    struct vector *ret = (struct vector *)malloc(sizeof(struct vector));

    ret->length = v1->length + v2->length;
    ret->data = (int *)malloc(sizeof(int) * ret->length);
    for (i = 0; i < v1->length; i++) {
        ret->data[i] = v1->data[i];
    }

    for (i = 0; i < v2->length; i++) {
        ret->data[v1->length + i] = v2->data[i];
    }

    return ret;
}


/**
 * Return an array of size *returnSize.
 * Note: The returned array must be malloced, assume caller calls free().
 */
int* diffWaysToCompute(char* input, int* returnSize)
{
    int operators[1024], operands[1024], n, i, j, k, r;
    char *tmp, *next;
    struct vector *left, *right, *prod, *tmp_v, **table;
    int *ret;


    // parse input to operators && operands
    for (tmp = input, n = 0; *tmp != '\0';) {
        operands[n++] = strtol(tmp, &next, 10);
        if (*next == '\0') break;
        operators[n - 1] = *next;
        tmp = next + 1;
    }

    // verify the parsing
    /*
    for (i = 0; i < n; i++) {
        printf("%d%c", operators[i], i < n -1 ? operands[i] : '\n');
    }
    */

    // alloc table
    table = (struct vector **)malloc(sizeof(struct vector*) * n * n);
    memset(table, 0, sizeof(struct vector *) * n * n);

    for (i = 0; i < n; i++) {
        for (j = 0; j + i < n; j++) {
            k = i * n + j;
            //printf("i = %d, j = %d, k = %d\n", i, j, k);
            if (i == 0) {
                table[k] = create_vector(1);
                table[k]->data[0] = operands[j];
            } else {
                table[k] = create_vector(0);
                for (r = 0; r < i; r++) {
                    left = table[r * n + j];
                    right = table[(i - 1 - r) * n + j + r + 1];
                    prod = mul(left, right, operators[j + r]);
                    tmp_v = concat(table[k], prod);
                    release_vector(table[k]);
                    table[k] = tmp_v;
                    //printf("r = %d\n", r);
                    //printf("left = "); print_vector(left);
                    //printf("right = "); print_vector(right);
                    //printf("prod = "); print_vector(prod);
                    release_vector(prod);
                }
            }
            //printf("table[k] = ");print_vector(table[k]);
        }
    }

    *returnSize = table[(n - 1) * n]->length;
    ret = (int *)malloc(sizeof(int) * (*returnSize));
    memcpy(ret, table[(n - 1) * n]->data, sizeof(int) * (*returnSize));

    for (i = 0; i < n * n; i++) {
        if (table[i]) release_vector(table[i]);
    }

    free(table);

    return ret;
}

int main()
{
    char *input = "2*3-4*5";

    int i, len, *ret;
    ret = diffWaysToCompute(input, &len);
    for (i = 0; i < len; i++) {
        printf("%d\n", ret[i]);
    }
    free(ret);
    return 0;
}
