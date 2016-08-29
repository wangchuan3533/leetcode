/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */
struct ListNode* mergeKLists(struct ListNode** lists, int listsSize) {
    struct ListNode* result = NULL, *tmp;

    int i, min_index;

    while (1) {
        for (i = 0, min_index = -1, tmp = NULL; i < listsSize; i++) {
            if (tmp == NULL || (lists[i] != NULL && lists[i]->val > tmp->val)) {
                tmp = lists[i];
                min_index = i;
            }
        }
        if (tmp != NULL) {
            lists[min_index] = tmp->next;
            tmp->next = result;
            result = tmp;
        } else {
            return result;
        }
    }
}
