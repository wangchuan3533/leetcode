#include <stdio.h>
#include <stdlib.h>
/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     struct TreeNode *left;
 *     struct TreeNode *right;
 * };
 */

struct TreeNode {
    int val;
    struct TreeNode *left;
    struct TreeNode *right;
};

struct TreeNode *sortedArrayToBST(int *nums, int numsSize)
{
    if (numsSize <= 0) {
        return NULL;
    }

    int half = numsSize >> 1;
    struct TreeNode *root = (struct TreeNode *)malloc(sizeof(struct TreeNode));
    root->val = nums[half];
    root->left = sortedArrayToBST(nums, half);
    root->right = sortedArrayToBST(nums + half + 1, numsSize - half - 1);

    return root;
}

int main()
{
    int nums[] = {-10, -3, 0, 5, 9};
    struct TreeNode *root = sortedArrayToBST(nums, 5);
    return 0;
}
