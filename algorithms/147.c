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


struct ListNode* insertionSortList(struct ListNode* head)
{
    struct ListNode *ret = NULL, *tmp, *pre, *cur;

    while (head != NULL) {
        tmp = head->next;
        
        for (pre = NULL, cur = ret; cur != NULL && cur->val < head->val; pre = cur, cur = cur->next);

        if (pre == NULL) {
            head->next = ret;
            ret = head;
        } else {
            pre->next = head;
            head->next = cur;
        }

        head = tmp;
    }

    return ret;
}

int main()
{
    int i;
    struct ListNode nodes[] = {
        {1, NULL},
        {4, NULL},
        {2, NULL},
        {4, NULL}
    }, *result;

    for (i = 0; i < 3; i++) {
        nodes[i].next = &nodes[i+1];
    }

    result = insertionSortList(&nodes[0]);

    while (result != NULL) {
        printf("%d\n", result->val);
        result = result->next;
    }

    return 0;
}
