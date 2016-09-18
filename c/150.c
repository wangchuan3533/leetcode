#include <stdio.h>
#include <stdlib.h>

int evalRPN(char** tokens, int tokensSize)
{
    int *stack = (int *)malloc(sizeof(int) * tokensSize), top = 0, i;
    int x, y, z;

#define MYPUSH(x) (stack[top++] = (x))
#define MYPOP() (stack[--top])

    for (i = 0; i < tokensSize; i++) {
        switch (tokens[i][0]) {
        case '+':
            if (tokens[i][1] == '\0') {
                y = MYPOP();
                x = MYPOP();
                z = x + y;
                MYPUSH(z);
            } else {
                MYPUSH(atoi(tokens[i]));
            }
            break;
        case '-':
            if (tokens[i][1] == '\0') {
                y = MYPOP();
                x = MYPOP();
                z = x - y;
                MYPUSH(z);
            } else {
                MYPUSH(atoi(tokens[i]));
            }
            break;
        case '*':
            y = MYPOP();
            x = MYPOP();
            z = x * y;
            MYPUSH(z);
            break;
        case '/':
            y = MYPOP();
            x = MYPOP();
            z = x / y;
            MYPUSH(z);
            break;
        default:
            MYPUSH(atoi(tokens[i]));
        }
    }

    z = MYPOP();
    free(stack);
    return z;
#undef MYPOP
#undef MYPUSH
}

int main()
{
    char *arr[] = {"4", "13", "5", "/", "+"};

    int ret = evalRPN(arr, 5);
    printf("ret = %d\n", ret);
    return 0;
}
