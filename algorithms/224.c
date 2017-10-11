#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int calculate(char* s)
{
    int *stack = (int *)malloc(sizeof(int) * strlen(s)), val, top = 0, ret = 0, factor, last;
#define PUSH(x) (stack[top++] = (x))
#define POP() (stack[--top])
    char *cur, *endptr;

    // guard
    factor = 1;
    last = 1;

    for (cur = s; *cur != '\0';) {
        switch (*cur) {
        case '0':
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
            val = strtol(cur, &endptr, 10);
            ret += last * factor * val;
            cur = endptr;
            break;
        case '+':
            last = 1;
            cur++;
            break;
        case '-':
            last = -1;
            cur++;
            break;
        case '(':
            PUSH(factor);
            factor *= last;
            last = 1;
            cur++;
            break;
        case ')':
            factor = POP();
            last = 1;
            cur++;
            break;
        case ' ':
            cur++;
            break;
        }
    }

#undef POP
#undef PUSH
    free(stack);
    return ret;
}

int main()
{
    //char *s = "0";
    //char *s = " 2-1 + 2 ";
    char *s = "(1+(4+5+2)-3)+(6+8)";
    int ret = calculate(s);
    printf("ret = %d\n", ret);
}
