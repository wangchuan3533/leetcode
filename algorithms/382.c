#include <stdlib.h>

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

typedef struct {
    struct ListNode *head;
} Solution;

/** @param head The linked list's head.
        Note that the head is guaranteed to be not null, so it contains at least one node. */
Solution* solutionCreate(struct ListNode* head) {
    Solution* result = (Solution *)malloc(sizeof(Solution));
    result->head = head;
    return result;
}

/** Returns a random node's value. */
int solutionGetRandom(Solution* obj) {
    ListNode *tmp;
    int i, current;
    long rnd;

    for (i = 1, tmp = obj->head; tmp != NULL; tmp = tmp->next, i++) {
        rnd = random() % i;
        if (rnd == 0) {
            current = tmp->val;
        }
    } 
    return current;
}

void solutionFree(Solution* obj) {
    
}

/**
 * Your Solution struct will be instantiated and called as such:
 * struct Solution* obj = solutionCreate(head);
 * int param_1 = solutionGetRandom(obj);
 * solutionFree(obj);
 */
