#include <stdio.h>
#include <stdlib.h>
#include "uthash.h"

typedef int bool;
#define true 1
#define false 0

struct result_node {
    int result;
    int selected;
    UT_hash_handle hh;
};

bool add_node(struct result_node **results, int selected, bool result)
{
    struct result_node *node = (struct result_node *)malloc(sizeof(struct result_node));
    memset(node, 0, sizeof(struct result_node));
    node->selected = selected;
    node->result = result;
    HASH_ADD(hh, *results, selected, sizeof(int), node);
    return result;
}

bool _canIWin(int maxChoosableInteger, int desiredTotal, int selected, struct result_node **results)
{
    struct result_node *tmp;
    HASH_FIND(hh, *results, &selected, sizeof(int), tmp);
    if (tmp) {
        return tmp->result;
    }

    for (int i = 0; i < maxChoosableInteger; i++) {
        if (selected & (1 << i)) {
            continue;
        }
        if ((i + 1) >= desiredTotal || !_canIWin(maxChoosableInteger, desiredTotal - i - 1, selected | (1 << i), results)) {
            return add_node(results, selected, true);
        }
    }

    return add_node(results, selected, false);
}

bool canIWin(int maxChoosableInteger, int desiredTotal)
{
    struct result_node *results = NULL;
    if ((maxChoosableInteger + 1) * maxChoosableInteger / 2 < desiredTotal) {
        return false;
    }
    bool ret = _canIWin(maxChoosableInteger, desiredTotal, 0, &results);
    HASH_CLEAR(hh, results);
    return ret;
}

int main()
{
    //int maxChoosableInteger = 10, desiredTotal = 11;
    //int maxChoosableInteger = 10, desiredTotal = 0;
    //int maxChoosableInteger = 10, desiredTotal = 40;
    int maxChoosableInteger = 5, desiredTotal = 50;
    bool ret = canIWin(maxChoosableInteger, desiredTotal);
    printf("ret = %d\n", ret);
    return 0;
}
  
