#include <string.h>
#include <stdio.h>
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
 struct ListNode {
     int val;
     struct ListNode *next;
 };

int cmp_list_node(struct ListNode *n1, struct ListNode *n2)
{
    if (n1 == NULL && n2 == NULL) return 0;
    if (n1 == NULL) return 1;
    if (n2 == NULL) return -1;

    if (n1->val == n2->val) return 0;
    if (n1->val > n2->val) return 1;
    return -1;
}

#define PARENT(x) (((x) - 1) >> 1)
#define LEFT_CHILD(x) (((x) << 1) + 1)
#define RIGHT_CHILE(x) (((x) << 1) + 2)

struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* result, *tmp, *reverted, *left, *right;
    int i, j, k;

    if (listsSize <= 0) return NULL;

    // construct heap
    for (i = 1; i < listsSize; i++) {
        for (j = i; j > 0;) {
            k = PARENT(j);
            if (cmp_list_node(lists[j], lists[k]) >= 0) {
                break;
            }

            tmp = lists[j];
            lists[j] = lists[k];
            lists[k] = tmp;
            j = k;
        }
    }

    result = NULL;
    while (lists[0] != NULL) {
        tmp = lists[0]->next;
        lists[0]->next = result;
        result = lists[0];
        lists[0] = tmp;
        for (i = 0; i < listsSize;) {
            j = LEFT_CHILD(i);
            k = RIGHT_CHILE(i);
            left = j < listsSize ? lists[j] : NULL;
            right = k < listsSize ? lists[k] : NULL;

            if (cmp_list_node(lists[i], left) <= 0 && cmp_list_node(lists[i], right) <= 0) {
                break;
            }

            if (cmp_list_node(left, right) < 0) {
                tmp = lists[i];
                lists[i] = lists[j];
                lists[j] = tmp;
                i = j;
            } else if (k < listsSize) {
                tmp = lists[i];
                lists[i] = lists[k];
                lists[k] = tmp;
                i = k;
            }
        }
    }

    for (reverted = NULL; result != NULL;) {
        tmp = result->next;
        result->next = reverted;
        reverted = result;
        result = tmp;
    }
    return reverted;
}
